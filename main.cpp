//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "/usr/include/linux/i2c-dev.h"
#include "/usr/include/linux/i2c.h"
#include "vocsensor.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QDebug>


QObject *vocSensor_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
//QQmlEngine *engine, QJSEngine *scriptEngine
//Stepper *Stepper::getInstance()
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    static VocSensor *m_vocSensor=nullptr;

    if (m_vocSensor==nullptr)
        m_vocSensor=new VocSensor();
    return m_vocSensor;
}



int main(int argc, char *argv[])
{
    int file;
    qDebug()<<"i2c test";

    if ((file = open("/dev/i2c-1", O_RDWR)) < 0)
    {
        qDebug()<<"Failed to open the i2c bus";
        exit(1);
    }
    else
        qDebug()<<"i2c bus OK";
    if (ioctl(file,I2C_SLAVE,0x48) < 0)
    {
        qDebug()<<"Failed to open the i2c device";
        exit(1);
    }
    else
        qDebug()<<"i2c device OK";

    char buf[10];

    int n=read(file,buf,3);
    {
        qDebug()<<n;
        qDebug()<<buf[0];
        qDebug()<<buf[1];
        qDebug()<<buf[2];
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
//    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<VocSensor>("quorum.VocSensor", 1, 0, "VocSensor", vocSensor_singleton_provider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
