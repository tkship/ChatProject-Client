#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include "global.h"

#include <QWidget>
#include <QTimer>

namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();

private:
    void ShowTips(const QString& aString);
    void ResetTips();
//    void SendVerifyCode();
    void ProcessVerifyCodeReply(const QJsonObject& aJson);
    void ProcessRegisterReply(const QJsonObject& aJson);

    void ChangeToSwitchPage();
    void ClearPages();

signals:
    void SigCancelButtonClicked();
    void UserRegisterSuccess();

private slots:
    void OnVerifyCodeButtonclick();
    void OnRecvReply(const QString& aRes, ReqId aId, ErrorCode aErr);

    void OnConfirmButtonclick();

    bool CheckUserName();
    bool CheckEmail();
    bool CheckPassword();
    bool CheckConfirmPwd();
    bool CheckVerifyCode();

private:
    Ui::RegisterWidget *ui;
    QTimer mTimer;
    int mCountDown;
};

#endif // REGISTERWIDGET_H
