#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include <QWidget>
#include <QTime>

class Measurement : public QWidget
{
public:
    Measurement(QWidget *parent = nullptr);
    void addParameters(int ver, long dOffset, QList<double> fCarriers, double fSampling, QString sType, QString sFormat,
                       int cIndex, QString dId, int sShift, long sAmount, int fileNr, QDate dat, QTime tLocal, QList<QString> comm);

    double getTimestamp();
    double getDuration();
    QTime getStartTime();
    QTime getEndTime();
    QString getDeviceId();
    int getChannelIndex();
    QString getComments();

    void setSelected();
    void setUnselected();
    bool isSelected();

private:
    int version;
    long dataOffset;

    QList<double> frequencyCarriers;

    double frequencySampling;

    QString sampleType;
    QString sampleFormat;

    int channelIndex;
    QString deviceId;

    int samplesShift;
    long samplesAmount;
    int fileNumber;

    QDate date;
    QTime timestampLocal;

    QList<QString> comments;

    bool selected=false;
    bool mightBeFaulty=false;

};

#endif // MEASUREMENT_H
