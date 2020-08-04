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
#include <QFile>
#include <QTextStream>

VocSensor::VocSensor(QObject *parent) : QObject(parent)
{
    sampleTimer = new QTimer();
    stopwatchTimer = new QTimer();
    stopwatchTimer->setSingleShot(false);
    connect (sampleTimer,SIGNAL(timeout()),this,SLOT(onSampleTimer()));
    connect (stopwatchTimer,SIGNAL(timeout()),this,SLOT(onStopwatchTimer()));

}

void VocSensor::setSampleIntervalms(int val){
    sampleIntervalValuems=val;
    sampleTimer->setInterval(sampleIntervalValuems);
    sampleIntervalmsChanged();
}

void VocSensor::initADC()
{
    int file;
    if ((file = open("/dev/i2c-1", O_RDWR)) < 0)
    {
        qDebug()<<"Failed to open the i2c bus";
        return;
    }
    // Get I2C device, ADS1100 I2C address is 0x48(72)
    ioctl(file, I2C_SLAVE, 0x48);

    // Select configuration register
    // Continuous conversion mode, 8 SPS, 1 PGA(0x0C)
    char config[1] = {0x0C};
    write(file, config, 1);
    sleep(1);

}

void VocSensor::onSampleTimer(void)
{
    int file;
    if ((file = open("/dev/i2c-1", O_RDWR)) < 0)
    {
//        qDebug()<<"Failed to open the i2c bus";
        return;
    }
    // Get I2C device, ADS1100 I2C address is 0x48(72)
    ioctl(file, I2C_SLAVE, 0x48);


    // Read 2 bytes of data
    // raw_adc msb, raw_adc lsb
    uchar data[2]={0};
    if(read(file, data, 2) != 2)
    {
//        qDebug()<<"Error : Input/output Error";
    }
    else
    {
        // Convert the data
        int raw_adc = (data[0] * 256 + data[1]);
        if(raw_adc > 32767)
        {
            raw_adc -= 65536;
        }

        double voltage=3.3*static_cast<double>(raw_adc)/32767;
        int timeDiff_sec=startTime.secsTo(QTime::currentTime());
        if (timeDiff_sec<0)     // If running over midnight, will give negative time value
            timeDiff_sec+=24*60*60; // Correct by adding 24 hours

        newSample(voltage, timeDiff_sec);
        sampleArray.append(Sample(voltage));
        setVocVoltage(voltage);
    }
}

void VocSensor::onStopwatchTimer()
{
    int timeDiffMs=startTime.msecsTo(QTime::currentTime());
    if (timeDiffMs<0)       // If running over midnight, will give negative time value
        timeDiffMs+=24*60*60*1000;  // add 24 hours to correct
    QTime stopwatchTime=QTime::fromMSecsSinceStartOfDay(timeDiffMs);
    setStopwatchString(stopwatchTime.toString("h:mm:ss"));
}

void VocSensor::startSampling()
{
    startTime=QTime::currentTime();
    stopwatchTimer->start(1000);
    onSampleTimer();
    sampleTimer->start(sampleIntervalms());
}

void VocSensor::stopSampling()
{
    sampleTimer->stop();
    stopwatchTimer->stop();
}

void VocSensor::clearSamples()
{
    sampleArray.clear();
}

void VocSensor::saveData()
{
    QString filename="/home/pi/vocData/";
    if (!sampleArray.empty())
    {
        Sample firstSample=sampleArray[0];
        Sample lastSample=sampleArray.last();
        filename+=lastSample.getSampleDate().toString("d-MMM-yy");
        filename+="  ";
        filename+=lastSample.getSampleTime().toString("hh-mm-ss");
        filename+=".csv";
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
              return;
        QTextStream out(&file);
        out<<"Date,Time,Voltage\n";
        for (auto &sample: sampleArray)
        {
            out << sample.getSampleDate().toString(("d-MMM-yy"))<<",";
            out << sample.getSampleTime().toString(("hh:mm:ss"))<<",";
            out << sample.getVoltage()<<"\n";
        }
        file.flush();
        file.close();
        newMessage("Save completed");

    }
}
