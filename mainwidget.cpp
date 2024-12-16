#include "mainwidget.h"

#include "websocketmgr.h"

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , mLoginWidget(new LoginWidget)
    , mRegisterWidget(new RegisterWidget)
    , mResetPwdWidget(new ResetPwdWidget)
    , mChatWidget(nullptr)
{
    InitWidget();

    mLoginWidget->show();
}

MainWidget::~MainWidget()
{
    ClearLoginWidget();

    mChatWidget->deleteLater();
}

void MainWidget::ClearLoginWidget()
{
    mLoginWidget->deleteLater();
    mRegisterWidget->deleteLater();
    mResetPwdWidget->deleteLater();

    mLoginWidget = nullptr;
    mRegisterWidget = nullptr;
    mResetPwdWidget = nullptr;
}

void MainWidget::InitWidget()
{
    // 登陆界面按钮点击事件
    connect(mLoginWidget, &LoginWidget::SigRegisterButtonClicked, this, &MainWidget::OnRegisterButtonClick);
    connect(mLoginWidget, &LoginWidget::SigResetPwdButtonClicked, this, &MainWidget::OnResetPwdButtonClick);

    // 注册界面按钮点击事件
    connect(mRegisterWidget, &RegisterWidget::SigCancelButtonClicked, this, &MainWidget::OnRegisterCancelButtonClick);
    connect(mRegisterWidget, &RegisterWidget::UserRegisterSuccess, this, &MainWidget::OnRegisterCancelButtonClick);

    // 重置密码界面按钮点击事件
    connect(mResetPwdWidget, &ResetPwdWidget::SigCancelButtonClicked, this, &MainWidget::OnResetPwdWidgetCancelButtonClick);
    connect(mResetPwdWidget, &ResetPwdWidget::ResetPwdSuccess, this, &MainWidget::OnResetPwdWidgetCancelButtonClick);

    // 连接到ChatServer
    connect(&WebSocketMgr::GetInstance(), &WebSocketMgr::SigConnected, this, &MainWidget::OnChatServerConnected);
}

void MainWidget::OnRegisterButtonClick()
{
    mLoginWidget->hide();
    mRegisterWidget->show();
}

void MainWidget::OnRegisterCancelButtonClick()
{
    mRegisterWidget->hide();
    mLoginWidget->show();
}

void MainWidget::OnResetPwdButtonClick()
{
    mLoginWidget->hide();
    mResetPwdWidget->show();
}

void MainWidget::OnResetPwdWidgetCancelButtonClick()
{
    mResetPwdWidget->hide();
    mLoginWidget->show();
}

void MainWidget::OnChatServerConnected()
{
    //显示ChatWidget界面
    mChatWidget = new ChatWidget;
    mChatWidget->show();

    //将登陆注册相关界面置为空
    ClearLoginWidget();
}
