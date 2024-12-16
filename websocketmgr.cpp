#include "websocketmgr.h"

WebSocketMgr::WebSocketMgr(QObject *parent)
    : QObject(parent)
    , mWebSocket(new QWebSocket)
{
    connect(mWebSocket, &QWebSocket::connected, this, &WebSocketMgr::OnConnected);
    connect(mWebSocket, &QWebSocket::disconnected, this, &WebSocketMgr::OnDisconnected);
    connect(mWebSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketMgr::OnBinaryMessageReceived);

//    connect(mWebSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &WebSocketMgr::OnError);

}

WebSocketMgr::~WebSocketMgr()
{
    mWebSocket->deleteLater();
}

WebSocketMgr &WebSocketMgr::GetInstance()
{
    static WebSocketMgr self;
    return self;
}

void WebSocketMgr::RegisterCallBack(ReqId aId, CallBackFunc aFunc)
{
    if(mCallBackMap.find(aId) != mCallBackMap.end())
    {
        assert(false);
        return;
    }

    // widget注册函数会有生命周期的问题。。。
    mCallBackMap[aId] = aFunc;
}

void WebSocketMgr::SetToken(const QString &aToken)
{
    mToken = aToken;
}

void WebSocketMgr::Connect(QUrl aUrl)
{
    mWebSocket->open(aUrl);
}

bool WebSocketMgr::Send(const QJsonObject& aJson)
{
    if(mWebSocket->state() != QAbstractSocket::SocketState::ConnectedState)
    {
        return false;
    }

    QByteArray data = QJsonDocument(aJson).toJson();
    mWebSocket->sendBinaryMessage(data);
    return true;
}

void WebSocketMgr::OnConnected()
{
    // 连接成功
    emit SigConnected();
}

void WebSocketMgr::OnDisconnected()
{
    // 断开连接
    // 如果服务器不在线，也会触发这个
    // 所以loginwidget和chatwidget都要绑定这个信号
    // loginwidget和chatwidget不会同时存在，所以只会有一个处理函数
    emit SigDisConnected();
}

//void WebSocketMgr::OnError(QAbstractSocket::SocketError)
//{
//    // 发生错误 --暂时用不到错误类型 统一解释为网络错误
//    emit SigConnectError();
//}

void WebSocketMgr::OnBinaryMessageReceived(const QByteArray& aMes)
{
    // 收到消息  -- 根据id注册回调，在这里调用回调
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(aMes).toUtf8());
    if(jsonDoc.isNull() || !jsonDoc.isObject())
    {
        qDebug("回传Json格式出错");
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    ReqId id = (ReqId)jsonObj["ReqId"].toInt();
    mCallBackMap[id]();
}
