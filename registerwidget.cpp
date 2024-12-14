#include "registerwidget.h"
#include "ui_registerwidget.h"

#include "global.h"
#include "util.h"
#include "httpmgr.h"

#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>

RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget),
    mTimer(this),
    mCountDown(5)
{
    ui->setupUi(this);
    setFixedSize(450, 600);

    // 返回确认按钮
    connect(ui->CancelButton, &QPushButton::clicked, this, &RegisterWidget::SigCancelButtonClicked);
    connect(ui->ConfirmButton, &QPushButton::clicked, this, &RegisterWidget::OnConfirmButtonclick);

    // 获取验证码
    connect(ui->VerifyCodeButton, &QPushButton::clicked, this, &RegisterWidget::OnVerifyCodeButtonclick);


    // 收到服务器回复时的回调
    connect(&HttpMgr::GetInstance(), &HttpMgr::SigModRegisterRecvReply, this, &RegisterWidget::OnRecvReply);

    // 检查输入栏
    connect(ui->UserNameLine, &QLineEdit::editingFinished, this, &RegisterWidget::CheckUserName);
    connect(ui->MailLine, &QLineEdit::editingFinished, this, &RegisterWidget::CheckEmail);
    connect(ui->PasswordLine, &QLineEdit::editingFinished, this, &RegisterWidget::CheckPassword);
    connect(ui->ConfirmPwdLine, &QLineEdit::editingFinished, this, &RegisterWidget::CheckConfirmPwd);
    connect(ui->VerifyCodeLine, &QLineEdit::editingFinished, this, &RegisterWidget::CheckVerifyCode);

    // 注册成功转换界面
    connect(ui->ConfirmButton2, &QPushButton::clicked, this, [this](){
        ClearPages();
        emit UserRegisterSuccess();
    });
    connect(&mTimer, &QTimer::timeout, this, [this](){
        mCountDown--;
        if(mCountDown < 0)
        {
            mTimer.stop();
            ClearPages();
            emit UserRegisterSuccess();
            return;
        }

        QString message = "注册成功，" + QString::number(mCountDown) + "秒后返回登陆界面";
        this->ui->MessageLabel2->setText(message);
    });
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::ShowTips(const QString& aString)
{
    ui->MessageLabel->setText(aString);
}

void RegisterWidget::ResetTips()
{
    ui->MessageLabel->setText("");
}

void RegisterWidget::SendVerifyCode()
{
    // 请求发送验证码


}

void RegisterWidget::ProcessVerifyCodeReply(const QJsonObject& aJson)
{
    if(aJson["error"].toInt() == ErrorCode::Success)
    {
        ShowTips("验证码已发至邮箱，请注意查收");
    }
    else
    {
        ShowTips("验证码请求出错");
    }
}

void RegisterWidget::ProcessRegisterReply(const QJsonObject &aJson)
{
    ErrorCode errorCode = ErrorCode(aJson["error"].toInt());
    if(errorCode == ErrorCode::Success)
    {
        ChangeToSwitchPage();
    }
    else if(errorCode == ErrorCode::VerifyCodeNotMatch)
    {
        ShowTips("验证码输入错误");
    }
    else if(errorCode == ErrorCode::MySQL_UserExist)
    {
        ShowTips("用户已存在，请重新注册");
    }
    else if(errorCode == ErrorCode::MySQL_Error || errorCode == ErrorCode::Redis_KeyNotFound)
    {
        ShowTips("服务器暂时无法响应，请稍后重试");
    }
}

void RegisterWidget::ChangeToSwitchPage()
{
    mTimer.start(1000);
    ui->StackedWidget->setCurrentWidget(ui->page_2);
}

void RegisterWidget::ClearPages()
{
    mCountDown = 5;
    ui->StackedWidget->setCurrentWidget(ui->page_1);
    ui->UserNameLine->setText("");
    ui->MailLine->setText("");
    ui->PasswordLine->setText("");
    ui->ConfirmPwdLine->setText("");
    ui->VerifyCodeLine->setText("");
    ui->MessageLabel->setText("提示框");
}

void RegisterWidget::OnVerifyCodeButtonclick()
{
    if(!CheckEmail())
    {
        return;
    }

    ResetTips();

    // 发送验证码
    QJsonObject jsonObj;
    jsonObj["email"] = ui->MailLine->text();
    HttpMgr::GetInstance().SendPostRequest(QUrl(GateServerPrefix + "GetVarifyCode"), jsonObj, Mod_Register, Req_VerifyCode);

}

void RegisterWidget::OnRecvReply(const QString &aRes, ReqId aId, ErrorCode aErr)
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
    case Req_VerifyCode:
        ProcessVerifyCodeReply(jsonObj);
        break;
    case Req_Register:
        ProcessRegisterReply(jsonObj);
        break;
    default:
        break;
    }

}

void RegisterWidget::OnConfirmButtonclick()
{
    if(!CheckUserName() || !CheckEmail() || !CheckPassword() || !CheckConfirmPwd() || !CheckVerifyCode())
    {
        return;
    }

    // 注册请求
    QString userName = ui->UserNameLine->text();
    QString email = ui->MailLine->text();
    QString password = ui->PasswordLine->text();
    QString confirmPwd = ui->ConfirmPwdLine->text();
    QString verifyCode = ui->VerifyCodeLine->text();

    QJsonObject jsonObj;
    jsonObj["userName"] = userName;
    jsonObj["email"] = email;
    jsonObj["password"] = Util::XORString(password);
    jsonObj["confirmPwd"] = Util::XORString(confirmPwd);
    jsonObj["verifyCode"] = verifyCode;

    HttpMgr::GetInstance().SendPostRequest(QUrl(GateServerPrefix + "Register"), jsonObj, Mod_Register, Req_Register);
}

bool RegisterWidget::CheckUserName()
{
    QString name = ui->UserNameLine->text();
    if(name.size() > 10)
    {
        ShowTips("用户名不能超过10个字符");
        return false;
    }

    ResetTips();
    return true;
}

bool RegisterWidget::CheckEmail()
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

bool RegisterWidget::CheckPassword()
{
    QString password = ui->PasswordLine->text();
    if(password.size() == 0)
    {
        ShowTips("密码不能为空");
        return false;
    }

    ResetTips();
    return true;
}

bool RegisterWidget::CheckConfirmPwd()
{
    QString password = ui->PasswordLine->text();
    QString confirmPwd = ui->ConfirmPwdLine->text();

    if(password != confirmPwd)
    {
        ShowTips("确认密码与密码不一致");
        return false;
    }

    ResetTips();
    return true;
}

bool RegisterWidget::CheckVerifyCode()
{
    QString verifyCode = ui->VerifyCodeLine->text();
    if(verifyCode.size() == 0)
    {
        ShowTips("验证码不能为空");
        return false;
    }

    ResetTips();
    return true;
}
