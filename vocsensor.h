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
    Q_PROPERTY(double VocReading READ VocReading WRITE  setVocReading NOTIFY VocReadingChanged)
    Q_PROPERTY(int sampleIntervalms READ sampleIntervalms WRITE  setSampleIntervalms NOTIFY sampleIntervalmsChanged)

public:
    explicit VocSensor(QObject *parent = nullptr);
    QTimer *sampleTimer;
    QTimer *stopwatchTimer;
    QString strTextMessage(void) {return textMessage;}
    QString stopwatchString(void) {return mstrStopwatchString;}
    double VocReading(void){return VocReadingValue;}
    int sampleIntervalms(void){return sampleIntervalValuems;}
    void setSampleIntervalms(int val);
    void setVocReading(double val){VocReadingValue=val;VocReadingChanged();}
    void setStrTextMessage(QString val){textMessage=val;strTextMessageChanged();}
    void setStopwatchString(QString val){mstrStopwatchString=val;stopwatchStringChanged();}
    void initADC(void);


signals:
    void strTextMessageChanged();
    void VocReadingChanged();
    void sampleIntervalmsChanged();
    void newSample(double vocReading, int sampleTime );
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
    double VocReadingValue;
    int sampleIntervalValuems=1000;
    QTime startTime;
    QString mstrStopwatchString;
};

#endif // VOCSENSOR_H
