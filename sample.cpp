#include "sample.h"

Sample::Sample(QObject *parent) : QObject(parent)
{

}
Sample::Sample(double val, QObject *parent ) : QObject(parent)
{
    sensorReading=val;
    sampleTime=QTime::currentTime();
    sampleDate=QDate::currentDate();
}

Sample::Sample(const Sample &sample):QObject(nullptr)
{
        sensorReading=sample.sensorReading;
        sampleTime=sample.sampleTime;
        sampleDate=sample.sampleDate;
}

Sample &Sample::Sample::operator=(const Sample &rhs)
{
    sensorReading=rhs.sensorReading;
    sampleTime=rhs.sampleTime;
    sampleDate=rhs.sampleDate;
    return *this;
}

