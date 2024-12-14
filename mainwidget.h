#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "loginwidget.h"
#include "registerwidget.h"
#include "resetpwdwidget.h"

#include <QMainWindow>

class MainWidget : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void OnRegisterButtonClick();
    void OnRegisterCancelButtonClick();
    void OnResetPwdButtonClick();
    void OnResetPwdWidgetCancelButtonClick();

private:
    LoginWidget* mLoginWidget;
    RegisterWidget* mRegisterWidget;
    ResetPwdWidget* mResetPwdWidget;


};

#endif // MAINWIDGET_H
