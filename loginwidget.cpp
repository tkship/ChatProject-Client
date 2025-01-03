#include "loginwidget.h"
#include "ui_loginwidget.h"

#include "httpmgr.h"
#include "websocketmgr.h"

#include "util.h"


LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(450, 600);

    // 确认，注册，重置密码按钮
    connect(ui->RegisterButton, &QPushButton::clicked, this, &LoginWidget::SigRegisterButtonClicked);
    connect(ui->ResetPwdButton, &QPushButton::clicked, this, &LoginWidget::SigResetPwdButtonClicked);
    connect(ui->LoginButton, &QPushButton::clicked, this, &LoginWidget::OnConfirmButtonClick);

    // 输入栏事件
    connect(ui->MailLine, &QLineEdit::textChanged, this, &LoginWidget::CheckInput);
    connect(ui->PasswordLine, &QLineEdit::textChanged, this, &LoginWidget::CheckInput);

    // 登陆事件回调
    connect(&HttpMgr::GetInstance(), &HttpMgr::SigModLoginRecvReply, this, &LoginWidget::OnRecvReply);

    // 连接ChatServer失败回调
    connect(&WebSocketMgr::GetInstance(), &WebSocketMgr::SigDisConnected, this, &LoginWidget::OnConnectError);
    // 连接ChatServer成功回调
    connect(&WebSocketMgr::GetInstance(), &WebSocketMgr::SigConnected, this, &LoginWidget::OnConnected);

    WebSocketMgr::GetInstance().RegisterCallBack(Chat_Login,
                                                 std::bind(&LoginWidget::ChatServerLoginCallBack, this, std::placeholders::_1));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}


void LoginWidget::ShowTips(const QString& aString)
{
    ui->MessageLabel->setText(aString);
}

void LoginWidget::ResetTips()
{
    ui->MessageLabel->setText("");
}

bool LoginWidget::CheckEmail()
{
    QString email = ui->MailLine->text();
    QRegularExpression re(R"((\w+)@(\w+)(\.)(\w+))");
    if(!re.match(email).hasMatch())
    {
        // 提示邮箱格式错误
        ShowTips("邮箱格式错误");
        return false;
    }

    ResetTips();
    return true;
}

void LoginWidget::ProcessLoginReply(const QJsonObject &aJson)
{
    if(aJson["error"].toInt() == ErrorCode::Success)
    {
        QString host = aJson["host"].toString();
        QString port = aJson["port"].toString();
        // json 传入时哪怕是int也应该是转为string，为什么这里用toString转不了呢？
        // 大概是QJsonObject内部自己把数字处理了"uid":"20"和"uid":20是不一样的
        // 所以用json也要保证收发端对数据类型的一致性
        mUid = aJson["uid"].toString();
        mToken = aJson["token"].toString();
        qDebug() << "[host]: " << host << "\n";
        qDebug() << "[port]: " << port << "\n";
        qDebug() << "[uid]: " << mUid << "\n";
        qDebug() << "[token]: " << mToken << "\n";

        QString chatServerAddress = WebSocketPrefix + host + ":" + port;
        WebSocketMgr::GetInstance().SetToken(mToken);
        WebSocketMgr::GetInstance().SetUid(mUid);
        WebSocketMgr::GetInstance().Connect(chatServerAddress);
    }
    else if(aJson["error"].toInt() == ErrorCode::MySQL_UserNotMatch)
    {
        // 查不到用户数据
        ShowTips("邮箱或密码错误");
    }
    else if(aJson["error"].toInt() == ErrorCode::GRPC_Failed)
    {
        ShowTips("连接服务器失败");
    }
}

void LoginWidget::ChatServerLoginCallBack(const QJsonObject& aJson)
{
    if(aJson["error"].toInt() == ErrorCode::Success)
    {
        emit SigLoginChatServerSuccess();
        return;
    }

    ShowTips("登陆失败");
}

void LoginWidget::OnRecvReply(const QString &aRes, ReqId aId, ErrorCode aErr)
{
    if(aErr == ErrorCode::NetFailure)
    {
        ShowTips("网络错误");
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(aRes.toUtf8());
    if(jsonDoc.isNull() || !jsonDoc.isObject())
    {
        ShowTips("回传Json格式出错");
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    switch(aId)
    {
    case Req_Login:
        ProcessLoginReply(jsonObj);
        break;
    default:
        break;
    }
}

void LoginWidget::OnConnectError()
{
    ShowTips("连接聊天服务器失败，请重试");
}

void LoginWidget::OnConnected()
{
    ShowTips("聊天服务连接成功，正在登陆...");
    // 发送token到ChatServer进行验证
    // 这里是一个请求Chat_Login
    // 对于ChatServer的回传数据，我们注册回调到websocketMgr即可
    QJsonObject jsonObj;
    jsonObj["msgId"] = Chat_Login;
    jsonObj["uid"] = mUid;
    jsonObj["token"] = mToken;

    qDebug() << "[uid]: " << mUid << "\n";
    qDebug() << "[token]: " << mToken << "\n";

    WebSocketMgr::GetInstance().Send(jsonObj);
}


void LoginWidget::OnConfirmButtonClick()
{
    if(!CheckEmail())
    {
        return;
    }

    // 登录
    QString email = ui->MailLine->text();
    QString password = ui->PasswordLine->text();

    QJsonObject jsonObj;
    jsonObj["email"] = email;
    jsonObj["password"] = Util::XORString(password);

    HttpMgr::GetInstance().SendPostRequest(QUrl(GateServerPrefix + "Login"), jsonObj, Mod_Login, Req_Login);
}

void LoginWidget::CheckInput()
{
    // 检查是否邮箱和密码栏都非空
    if(!CheckEmail() || ui->PasswordLine->text().isEmpty())
    {
        ui->LoginButton->setEnabled(false);
        return;
    }

    ui->LoginButton->setEnabled(true);
}

