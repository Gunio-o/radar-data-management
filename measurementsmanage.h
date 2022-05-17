#ifndef MEASUREMENTMANAGE_H
#define MEASUREMENTMANAGE_H

#include <QObject>
#include <QWidget>
#include "measurement.h"
#include "timeline.h"

class MeasurementsManage
{
public:
    MeasurementsManage();
    void createTimelines(QList<Measurement*> *mList);
    void addTimeline(QString dId, int chId, QTime startT, QTime endT);
    void addMeasurement(int ver, long dOffset, QList<double> fCarriers, double fSampling, QString sType, QString sFormat,
                        int cIndex, QString dId, int sShift, long sAmount, int fileNr, QDate dat, QTime tLocal, QList<QString> comm);

protected:
    QList<Timeline*> *timelineList;
    QList<Measurement*> *measurementList;
    QList<QLabel *> *timelineLabelList;
    QTime startTime;
    QTime endTime;

};

#endif // MEASUREMENTMANAGE_H
