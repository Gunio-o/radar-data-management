#include "measurement.h"

Measurement::Measurement(QWidget *parent) : QWidget(parent)
{

}


void Measurement::addParameters(int ver, long dOffset, QList<double> fCarriers, double fSampling, QString sType, QString sFormat, int cIndex, QString dId, int sShift, long sAmount, int fileNr, QDate dat, QTime tLocal, QList<QString> comm)
{
    version = ver;
    dataOffset = dOffset;

    frequencyCarriers = fCarriers;

    frequencySampling = fSampling;

    sampleType = sType;
    sampleFormat = sFormat;

    channelIndex = cIndex;
    deviceId = dId;

    samplesShift = sShift;
    samplesAmount = sAmount;
    fileNumber = fileNr;

    date = dat;
    timestampLocal = tLocal;

    comments = comm;

    setToolTip("fc="+QString::number(frequencyCarriers.last())+"\n"+
               "fs="+QString::number(frequencySampling)+"\n"+
               "sample amount="+QString::number(samplesAmount)+"\n"+
               "sample type="+sampleType+"\n"+
               "sample format="+sampleFormat+"\n"+
               "date "+date.toString()+"\n"+
               "timestamp="+timestampLocal.toString()+"\n");
}

double Measurement::getTimestamp()
{
    return timestampLocal.msecsSinceStartOfDay();
}

QTime Measurement::getStartTime()
{
    return timestampLocal;
}

QTime Measurement::getEndTime()
{
    return timestampLocal.addMSecs(getDuration());
}


double Measurement::getDuration()
{
    return samplesAmount*1000/frequencySampling;
}

QString Measurement::getDeviceId()
{
    return deviceId;
}

int Measurement::getChannelIndex()
{
    return channelIndex;
}

QString Measurement::getComments()
{
    QString text;
    for (int i=0;i<comments.size();i++) {
        text.append(comments.at(i));
    }
    return text;
}

void Measurement::setSelected()
{
    selected = true;
}

void Measurement::setUnselected()
{
    selected = false;
}

bool Measurement::isSelected()
{
    return selected;
}
