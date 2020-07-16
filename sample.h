#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include <QTime>

class Sample : public QObject
{
    Q_OBJECT
public:
    explicit Sample(QObject *parent = nullptr);
    Sample (float voltage, QObject *parent = nullptr);
    Sample(const Sample& );
    Sample& operator=(const Sample&);

signals:
    private:
    float voltage;
    QTime sampleTime;


public slots:
};

#endif // SAMPLE_H
