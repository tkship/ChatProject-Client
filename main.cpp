#include "mainwidget.h"

#include "global.h"

#include <QApplication>
#include <QSettings>
//#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;

    QIcon icon(":/res/chat.ico"); // 使用资源文件路径
    a.setWindowIcon(icon);

    QString configFileName = "config.ini";
    QString appPath = QCoreApplication::applicationDirPath();
    QString configFilePath = QDir::toNativeSeparators(appPath + QDir::separator() + configFileName);

    QSettings settings(configFilePath, QSettings::IniFormat);
    QString host = settings.value("GateServer/host").toString();
    QString port = settings.value("GateServer/port").toString();
    GateServerPrefix = "http://" + host + ":" + port + '/';


    return a.exec();
}
