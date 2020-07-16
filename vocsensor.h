#ifndef VOCSENSOR_H
#define VOCSENSOR_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include "sample.h"

class VocSensor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString strTextMessage READ strTextMessage WRITE  setStrTextMessage NOTIFY strTextMessageChanged)

public:
    explicit VocSensor(QObject *parent = nullptr);
    QTimer *sampleTimer;
    QString strTextMessage(void) {return textMessage;}
    void setStrTextMessage(QString val){textMessage=val;strTextMessageChanged();}

signals:
    void strTextMessageChanged();
    void newSample(float voltage);

public slots:
    void onSampleTimer(void);

private:
    QString textMessage=tr("");
    QVector<Sample> sampleArray;
};

#endif // VOCSENSOR_H
