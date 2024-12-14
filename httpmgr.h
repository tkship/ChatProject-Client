#ifndef HTTPMGR_H
#define HTTPMGR_H

#include "global.h"

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>



class HttpMgr : public QObject
{
    Q_OBJECT
public:
    explicit HttpMgr(QObject *parent = nullptr);
    ~HttpMgr();

    static HttpMgr& GetInstance();

    void SendPostRequest(QUrl aUrl, const QJsonObject& aJson, Module aMod, ReqId aId);

private:
    void AfterRecvReply(const QString& aRes, Module aMod, ReqId aId, ErrorCode aErr);

signals:
    void SigModRegisterRecvReply(const QString& aRes, ReqId aId, ErrorCode aErr);
    void SigModResetPwdRecvReply(const QString& aRes, ReqId aId, ErrorCode aErr);

private:
    QNetworkAccessManager mNetMgr;

};

#endif // HTTPMGR_H
