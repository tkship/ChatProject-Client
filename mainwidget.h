#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "loginwidget.h"
#include "registerwidget.h"
#include "resetpwdwidget.h"
#include "chatwidget.h"

#include <QMainWindow>

class MainWidget : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    // 当转到ChatWidget时将登录相关界面析构，释放内存
    void ClearLoginWidget();
    // 建立相关信号与槽
    void InitWidget();

private slots:
    void OnRegisterButtonClick();
    void OnRegisterCancelButtonClick();
    void OnResetPwdButtonClick();
    void OnResetPwdWidgetCancelButtonClick();
    void OnChatServerConnected();

private:
    LoginWidget* mLoginWidget;
    RegisterWidget* mRegisterWidget;
    ResetPwdWidget* mResetPwdWidget;
    ChatWidget* mChatWidget;

};

#endif // MAINWIDGET_H
