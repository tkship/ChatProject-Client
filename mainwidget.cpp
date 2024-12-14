#include "mainwidget.h"


MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , mLoginWidget(new LoginWidget)
    , mRegisterWidget(new RegisterWidget)
{
    mLoginWidget->show();

    connect(mLoginWidget, &LoginWidget::SigRegisterButtonClicked, this, &MainWidget::OnRegisterButtonClick);
    connect(mRegisterWidget, &RegisterWidget::SigCancelButtonClicked, this, &MainWidget::OnCancelButtonClick);
    connect(mRegisterWidget, &RegisterWidget::UserRegisterSuccess, this, &MainWidget::OnCancelButtonClick);

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

void MainWidget::OnCancelButtonClick()
{
    mRegisterWidget->hide();
    mLoginWidget->show();
}
