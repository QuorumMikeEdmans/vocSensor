#include "sample.h"

Sample::Sample(QObject *parent) : QObject(parent)
{

}
Sample::Sample(double val, QObject *parent ) : QObject(parent)
{
    voltage=val;
    sampleTime=QTime::currentTime();
}

Sample::Sample(const Sample &sample):QObject(nullptr)
{
        voltage=sample.voltage;
        sampleTime=sample.sampleTime;

}

Sample &Sample::Sample::operator=(const Sample &rhs)
{
    voltage=rhs.voltage;
    sampleTime=rhs.sampleTime;
    return *this;
}

