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
    Q_PROPERTY(QString stopwatchString READ stopwatchString WRITE  setStopwatchString NOTIFY stopwatchStringChanged)
    Q_PROPERTY(double vocVoltage READ vocVoltage WRITE  setVocVoltage NOTIFY vocVoltageChanged)
    Q_PROPERTY(int sampleIntervalms READ sampleIntervalms WRITE  setSampleIntervalms NOTIFY sampleIntervalmsChanged)

public:
    explicit VocSensor(QObject *parent = nullptr);
    QTimer *sampleTimer;
    QTimer *stopwatchTimer;
    QString strTextMessage(void) {return textMessage;}
    QString stopwatchString(void) {return mstrStopwatchString;}
    double vocVoltage(void){return vocVoltageValue;}
    int sampleIntervalms(void){return sampleIntervalValuems;}
    void setSampleIntervalms(int val);
    void setVocVoltage(double val){vocVoltageValue=val;vocVoltageChanged();}
    void setStrTextMessage(QString val){textMessage=val;strTextMessageChanged();}
    void setStopwatchString(QString val){mstrStopwatchString=val;stopwatchStringChanged();}
    void initADC(void);


signals:
    void strTextMessageChanged();
    void vocVoltageChanged();
    void sampleIntervalmsChanged();
    void newSample(double voltage, int sampleTime );
    void stopwatchStringChanged();
    void newMessage(QString message);

public slots:
    void onSampleTimer(void);
    void onStopwatchTimer(void);
    void startSampling(void);
    void stopSampling(void);
    void clearSamples(void);
    void saveData(void);

private:
    QString textMessage=tr("");
    QVector<Sample> sampleArray;
    double vocVoltageValue;
    int sampleIntervalValuems=1000;
    QTime startTime;
    QString mstrStopwatchString;
};

#endif // VOCSENSOR_H
