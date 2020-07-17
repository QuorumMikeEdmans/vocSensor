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
    Q_PROPERTY(double vocVoltage READ vocVoltage WRITE  setVocVoltage NOTIFY vocVoltageChanged)

public:
    explicit VocSensor(QObject *parent = nullptr);
    QTimer *sampleTimer;
    QString strTextMessage(void) {return textMessage;}
    double vocVoltage(void){return vocVoltageValue;}
    void setVocVoltage(double val){vocVoltageValue=val;vocVoltageChanged();}
    void setStrTextMessage(QString val){textMessage=val;strTextMessageChanged();}

signals:
    void strTextMessageChanged();
    void vocVoltageChanged();
    void newSample(double voltage);

public slots:
    void onSampleTimer(void);

private:
    QString textMessage=tr("");
    QVector<Sample> sampleArray;
    double vocVoltageValue;
};

#endif // VOCSENSOR_H
