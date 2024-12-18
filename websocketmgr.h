#ifndef WEBSOCKETMGR_H
#define WEBSOCKETMGR_H

#include "global.h"

#include <QObject>
#include <QWebSocket>

#include "unordered_map"

class WebSocketMgr : public QObject
{
    Q_OBJECT

    typedef std::function<void(const QJsonObject&)> CallBackFunc;
public:
    explicit WebSocketMgr(QObject *parent = nullptr);
    ~WebSocketMgr();

    static WebSocketMgr& GetInstance();

    void RegisterCallBack(MsgId aId, CallBackFunc aFunc);
    void SetToken(const QString& aToken);
    QString& GetToken();
    void SetUid(const QString& aUid);
    QString& GetUid();

    void Connect(QUrl aUrl);
    bool Send(const QJsonObject& aJson);
signals:
    void SigConnected();
    void SigDisConnected();
    void SigRecvMsgFromChatServer(const QByteArray& aMsg);
//    void SigConnectError();

private slots:
    void OnConnected();
    void OnDisconnected();
//    void OnError(QAbstractSocket::SocketError);
    void OnTextMessageReceived(const QString& aMsg);
private:
    QWebSocket* mWebSocket;
    std::unordered_map<MsgId, CallBackFunc> mCallBackMap;
    QString mToken;
    QString mUid;
};

#endif // WEBSOCKETMGR_H
