#ifndef WEBSOCKETMGR_H
#define WEBSOCKETMGR_H

#include "global.h"

#include <QObject>
#include <QWebSocket>

#include "unordered_map"

class WebSocketMgr : public QObject
{
    Q_OBJECT

    typedef std::function<void()> CallBackFunc;
public:
    explicit WebSocketMgr(QObject *parent = nullptr);
    ~WebSocketMgr();

    static WebSocketMgr& GetInstance();

    void RegisterCallBack(ReqId aId, CallBackFunc aFunc);
    void SetToken(const QString& aToken);

    void Connect(QUrl aUrl);
    bool Send(const QJsonObject& aJson);
signals:
    void SigConnected();
    void SigDisConnected();
    void SigRecvMesFromChatServer(const QByteArray& aMes);
//    void SigConnectError();

private slots:
    void OnConnected();
    void OnDisconnected();
//    void OnError(QAbstractSocket::SocketError);
    void OnBinaryMessageReceived(const QByteArray& aMes);
private:
    QWebSocket* mWebSocket;
    std::unordered_map<ReqId, CallBackFunc> mCallBackMap;
    QString mToken;
};

#endif // WEBSOCKETMGR_H
