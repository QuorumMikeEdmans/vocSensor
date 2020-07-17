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

signals:
    private:
    double voltage;
    QTime sampleTime;


public slots:
};

#endif // SAMPLE_H
