#include "resetpwdwidget.h"
#include "ui_resetpwdwidget.h"

#include "httpmgr.h"
#include "util.h"

#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>

ResetPwdWidget::ResetPwdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetPwdWidget),
    mTimer(this),
    mCountDown(5)
{
    ui->setupUi(this);

    // 确认取消按钮
    connect(ui->CancelButton, &QPushButton::clicked, this, &ResetPwdWidget::SigCancelButtonClicked);
    connect(ui->ConfirmButton, &QPushButton::clicked, this, &ResetPwdWidget::OnConfirmButtonclick);

    // 获取验证码
    connect(ui->VerifyCodeButton, &QPushButton::clicked, this, &ResetPwdWidget::OnVerifyCodeButtonclick);

    // 收到服务器回复时的回调
    connect(&HttpMgr::GetInstance(), &HttpMgr::SigModResetPwdRecvReply, this, &ResetPwdWidget::OnRecvReply);

    // 检查输入栏
    connect(ui->MailLine, &QLineEdit::editingFinished, this, &ResetPwdWidget::CheckEmail);
    connect(ui->PasswordLine, &QLineEdit::editingFinished, this, &ResetPwdWidget::CheckPassword);
    connect(ui->ConfirmPwdLine, &QLineEdit::editingFinished, this, &ResetPwdWidget::CheckConfirmPwd);
    connect(ui->VerifyCodeLine, &QLineEdit::editingFinished, this, &ResetPwdWidget::CheckVerifyCode);

    // 注册成功转换界面
    connect(ui->ConfirmButton2, &QPushButton::clicked, this, [this](){
        ClearPages();
        emit ResetPwdSuccess();
    });
    connect(&mTimer, &QTimer::timeout, this, [this](){
        mCountDown--;
        if(mCountDown < 0)
        {
            mTimer.stop();
            ClearPages();
            emit ResetPwdSuccess();
            return;
        }

        QString message = "密码重置成功，" + QString::number(mCountDown) + "秒后返回登陆界面";
        this->ui->MessageLabel2->setText(message);
    });
}

ResetPwdWidget::~ResetPwdWidget()
{
    delete ui;
}

void ResetPwdWidget::ProcessVerifyCodeReply(const QJsonObject &aJson)
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

void ResetPwdWidget::ProcessResetPwdReply(const QJsonObject &aJson)
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
    else if(errorCode == ErrorCode::MySQL_UserNotExist)
    {
        ShowTips("用户不存在，请先进行注册");
    }
    else if(errorCode == ErrorCode::MySQL_Error || errorCode == ErrorCode::Redis_KeyNotFound)
    {
        ShowTips("服务器暂时无法响应，请稍后重试");
    }
}

void ResetPwdWidget::OnConfirmButtonclick()
{
    if(!CheckEmail() || !CheckPassword() || !CheckConfirmPwd() || !CheckVerifyCode())
    {
        return;
    }

    QString email = ui->MailLine->text();
    QString password = ui->PasswordLine->text();
    QString confirmPwd = ui->ConfirmPwdLine->text();
    QString verifyCode = ui->VerifyCodeLine->text();

    QJsonObject jsonObj;
    jsonObj["email"] = email;
    jsonObj["password"] = Util::XORString(password);
    jsonObj["confirmPwd"] = Util::XORString(confirmPwd);
    jsonObj["verifyCode"] = verifyCode;

    HttpMgr::GetInstance().SendPostRequest(QUrl(GateServerPrefix + "ResetPwd"), jsonObj, Mod_ResetPwd, Req_ResetPwd);
}

void ResetPwdWidget::OnVerifyCodeButtonclick()
{
    if(!CheckEmail())
    {
        return;
    }

    ResetTips();

    // 发送验证码
    QJsonObject jsonObj;
    jsonObj["email"] = ui->MailLine->text();
    HttpMgr::GetInstance().SendPostRequest(QUrl(GateServerPrefix + "GetVarifyCode"), jsonObj, Mod_ResetPwd, Req_VerifyCode);
}

void ResetPwdWidget::ShowTips(const QString& aString)
{
    ui->MessageLabel->setText(aString);
}

void ResetPwdWidget::ResetTips()
{
    ui->MessageLabel->setText("");
}

bool ResetPwdWidget::CheckEmail()
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

bool ResetPwdWidget::CheckPassword()
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

bool ResetPwdWidget::CheckConfirmPwd()
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

bool ResetPwdWidget::CheckVerifyCode()
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

void ResetPwdWidget::ChangeToSwitchPage()
{
    mTimer.start(1000);
    ui->StackedWidget->setCurrentWidget(ui->page_2);
}

void ResetPwdWidget::ClearPages()
{
    mCountDown = 5;
    ui->StackedWidget->setCurrentWidget(ui->page_1);
    ui->MailLine->setText("");
    ui->PasswordLine->setText("");
    ui->ConfirmPwdLine->setText("");
    ui->VerifyCodeLine->setText("");
    ui->MessageLabel->setText("提示框");
}


void ResetPwdWidget::OnRecvReply(const QString &aRes, ReqId aId, ErrorCode aErr)
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
    case Req_ResetPwd:
        ProcessResetPwdReply(jsonObj);
        break;
    default:
        break;
    }

}
