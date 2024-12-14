#include "httpmgr.h"

#include <QJsonDocument>
#include <QNetworkReply>

HttpMgr::HttpMgr(QObject *parent)
    : QObject(parent)
{

}

HttpMgr::~HttpMgr()
{

}

HttpMgr &HttpMgr::GetInstance()
{
    static HttpMgr self;
    return self;
}

void HttpMgr::SendPostRequest(QUrl aUrl, const QJsonObject &aJson, Module aMod, ReqId aId)
{
    QByteArray data = QJsonDocument(aJson).toJson();
    QNetworkRequest request(aUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    QNetworkReply* reply = mNetMgr.post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [this, reply, aMod, aId](){
        if(reply->error() != QNetworkReply::NoError)
        {
            qDebug() << reply->errorString();
            AfterRecvReply("", aMod, aId, ErrorCode::NetFailure);
            reply->deleteLater();
            return;
        }

        QString res = reply->readAll();
        AfterRecvReply(res, aMod, aId, ErrorCode::Success);
        reply->deleteLater();
    });
}

void HttpMgr::AfterRecvReply(const QString& aRes, Module aMod, ReqId aId, ErrorCode aErr)
{
    if(aMod == Mod_Register)
    {
        emit SigModRegisterRecvReply(aRes, aId, aErr);
    }
}
