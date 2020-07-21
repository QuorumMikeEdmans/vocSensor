#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include <QTime>

class Sample : public QObject
{
    Q_OBJECT
public:
    explicit Sample(QObject *parent = nullptr);
    Sample (double voltage, QObject *parent = nullptr);
    Sample(const Sample& );
    Sample& operator=(const Sample&);
    QTime getSampleTime(void){return sampleTime;}
    QDate getSampleDate(void){return sampleDate;}
    double getVoltage(void){return voltage;}

signals:
    private:
    double voltage;
    QTime sampleTime;
    QDate sampleDate;

public slots:
};

#endif // SAMPLE_H
