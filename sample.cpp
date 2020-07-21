#include "sample.h"

Sample::Sample(QObject *parent) : QObject(parent)
{

}
Sample::Sample(double val, QObject *parent ) : QObject(parent)
{
    voltage=val;
    sampleTime=QTime::currentTime();
    sampleDate=QDate::currentDate();
}

Sample::Sample(const Sample &sample):QObject(nullptr)
{
        voltage=sample.voltage;
        sampleTime=sample.sampleTime;
        sampleDate=sample.sampleDate;
}

Sample &Sample::Sample::operator=(const Sample &rhs)
{
    voltage=rhs.voltage;
    sampleTime=rhs.sampleTime;
    sampleDate=rhs.sampleDate;
    return *this;
}

