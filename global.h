#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <QString>
#include <QDir>
#include <QWidget>
#include <QStyle>
#include <QAction>
//#include <QCursor>

#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>

extern QString GateServerPrefix;
extern QString WebSocketPrefix;

void RePolish(QWidget* aSelf);

namespace CP
{

// 用来定位模块
enum Module
{
    Mod_Register = 0,
    Mod_ResetPwd,
    Mod_Login
};

// Http请求GateServer
enum ReqId
{   
    Req_VerifyCode = 0,
    Req_Register,
    Req_ResetPwd,
    Req_Login,
};

// WebSocket请求ChatServer
enum MsgId
{
    Chat_Login = 0,
};

enum ErrorCode
{
    Success = 0,
    GRPC_Failed = 1001,
    Redis_KeyNotFound = 1002,
    VerifyCodeNotMatch = 1003,
    MySQL_UserExist = 1004,
    MySQL_Error = 1005,
    MySQL_UserNotExist = 1006,
    MySQL_UserNotMatch = 1007,
    Json_ParseError = 1008,
    Server_Failed = 1009, // 加一个笼统的错误码表示服务器某处崩溃了

    Chat_InvalidMsgId = 2001,
    Chat_InvalidUser = 2002,

    NetFailure = 10001,

};
}

using namespace CP;
#endif // GLOBAL_H
