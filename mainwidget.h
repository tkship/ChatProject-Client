#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "loginwidget.h"
#include "registerwidget.h"

#include <QMainWindow>

class MainWidget : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void OnRegisterButtonClick();
    void OnCancelButtonClick();

private:
    LoginWidget* mLoginWidget;
    RegisterWidget* mRegisterWidget;


};

#endif // MAINWIDGET_H
