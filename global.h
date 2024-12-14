#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QDir>

extern QString GateServerPrefix;

namespace CP
{

// 用来定位模块
enum Module
{
    Mod_Register,
    Mod_ResetPwd
};

// 用来定位模块内的具体哪个发送请求
enum ReqId
{
    Req_VerifyCode,
    Req_Register,
    Req_ResetPwd,
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

    NetFailure = 10001,

};
}

using namespace CP;
#endif // GLOBAL_H
