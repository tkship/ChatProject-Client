#ifndef UTIL_H
#define UTIL_H

#include <QString>

namespace Util
{

QString XORString(const QString& aStr)
{
    // 对每个字节异或
    std::string temp = aStr.toStdString();
    int size = temp.size();
    std::string outTemp(size, 0);
    char factor = size % 255;

    for(int i = 0; i < size; ++i)
    {
        outTemp[i] = factor ^ temp[i];
    }

    // 加密后长度不一定相等，反向可能无法解密
    return QString(outTemp.c_str());
}
}

#endif // UTIL_H
