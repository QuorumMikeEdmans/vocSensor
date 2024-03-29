#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include <QTime>

class Sample : public QObject
{
    Q_OBJECT
public:
    explicit Sample(QObject *parent = nullptr);
    Sample (double sensorReading, QObject *parent = nullptr);
    Sample(const Sample& );
    Sample& operator=(const Sample&);
    QTime getSampleTime(void){return sampleTime;}
    QDate getSampleDate(void){return sampleDate;}
    double getSensorReading(void){return sensorReading;}

signals:
    private:
    double sensorReading;
    QTime sampleTime;
    QDate sampleDate;

public slots:
};

#endif // SAMPLE_H
