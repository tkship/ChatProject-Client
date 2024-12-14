#ifndef RESETPWDWIDGET_H
#define RESETPWDWIDGET_H

#include "global.h"

#include <QWidget>
#include <QTimer>

namespace Ui {
class ResetPwdWidget;
}

class ResetPwdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResetPwdWidget(QWidget *parent = nullptr);
    ~ResetPwdWidget();

signals:
    void SigCancelButtonClicked();
    void ResetPwdSuccess();

private:
    void ProcessVerifyCodeReply(const QJsonObject& aJson);
    void ProcessResetPwdReply(const QJsonObject& aJson);

    void OnConfirmButtonclick();

    void ShowTips(const QString& aString);
    void ResetTips();

    bool CheckEmail();
    bool CheckPassword();
    bool CheckConfirmPwd();
    bool CheckVerifyCode();

    void ChangeToSwitchPage();
    void ClearPages();

private slots:
    void OnVerifyCodeButtonclick();
    void OnRecvReply(const QString& aRes, ReqId aId, ErrorCode aErr);

private:
    Ui::ResetPwdWidget *ui;
    QTimer mTimer;
    int mCountDown;
};

#endif // RESETPWDWIDGET_H
