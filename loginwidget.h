#ifndef WIDGET_H
#define WIDGET_H

#include "global.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

signals:
    void SigRegisterButtonClicked();
    void SigResetPwdButtonClicked();

private:
    void ShowTips(const QString& aString);
    void ResetTips();
    bool CheckEmail();

    void ProcessLoginReply(const QJsonObject& aJson);

private slots:
    void OnConfirmButtonClick();
    void CheckInput();
    void OnRecvReply(const QString &aRes, ReqId aId, ErrorCode aErr);
    void OnConnectError();
    void OnConnected();


private:
    Ui::Widget *ui;
    std::string mUid;
    std::string mToken;
};
#endif // WIDGET_H
