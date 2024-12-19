#include "mainwidget.h"

#include "global.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;

    QFile qss(":/qss/style.qss");
    if(qss.open(QFile::ReadOnly))
    {
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else
    {
        qDebug() << "加载qss文件出错";
    }

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
