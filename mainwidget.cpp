#include "mainwidget.h"


MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , mLoginWidget(new LoginWidget)
    , mRegisterWidget(new RegisterWidget)
    , mResetPwdWidget(new ResetPwdWidget)
{
    mLoginWidget->show();

    // 登陆界面按钮点击事件
    connect(mLoginWidget, &LoginWidget::SigRegisterButtonClicked, this, &MainWidget::OnRegisterButtonClick);
    connect(mLoginWidget, &LoginWidget::SigResetPwdButtonClicked, this, &MainWidget::OnResetPwdButtonClick);

    // 注册界面按钮点击事件
    connect(mRegisterWidget, &RegisterWidget::SigCancelButtonClicked, this, &MainWidget::OnRegisterCancelButtonClick);
    connect(mRegisterWidget, &RegisterWidget::UserRegisterSuccess, this, &MainWidget::OnRegisterCancelButtonClick);

    // 重置密码界面按钮点击事件
    connect(mResetPwdWidget, &ResetPwdWidget::SigCancelButtonClicked, this, &MainWidget::OnResetPwdWidgetCancelButtonClick);
    connect(mResetPwdWidget, &ResetPwdWidget::ResetPwdSuccess, this, &MainWidget::OnResetPwdWidgetCancelButtonClick);
}

MainWidget::~MainWidget()
{
    if(mLoginWidget)
    {
        delete mLoginWidget;
        mLoginWidget = nullptr;
    }
    if(mRegisterWidget)
    {
        delete mRegisterWidget;
        mLoginWidget = nullptr;
    }
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
