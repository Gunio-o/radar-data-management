#include "measurementsmanage.h"

MeasurementsManage::MeasurementsManage()
{
    timelineList = new QList<Timeline*>();
    measurementList = new QList<Measurement*>();
    timelineLabelList = new QList<QLabel*>();
}

void MeasurementsManage::createTimelines(QList<Measurement*> *mList)
{
    QVector<QString> deviceIdList;
    QVector<int> channelIndexList;
    QTime startT = QTime(23,59);
    QTime endT = QTime(0,0);
    for (int i=0; i<mList->size(); i++) {

        if(mList->at(i)->getStartTime() < startT)
            startT = mList->at(i)->getStartTime();
        if(mList->at(i)->getEndTime() > endT)
            endT = mList->at(i)->getEndTime();
    }
    startTime = startT;
    endTime = endT;

    for (int i=0; i<mList->size(); i++){
        if(!deviceIdList.contains(mList->at(i)->getDeviceId()) ||
                !channelIndexList.contains(mList->at(i)->getChannelIndex()))
        {
            deviceIdList.append(mList->at(i)->getDeviceId());
            channelIndexList.append(mList->at(i)->getChannelIndex());
            addTimeline(mList->at(i)->getDeviceId(),mList->at(i)->getChannelIndex(),startT,endT);
        }
    }

    for (int j=0; j<timelineList->size(); j++){
        for (int k=0; k<mList->size(); k++){
            if(mList->at(k)->getDeviceId()==timelineList->at(j)->getDeviceId() &&
                   mList->at(k)->getChannelIndex()==timelineList->at(j)->getChannelIndex() ){
                timelineList->at(j)->addMeasurement(mList->at(k));
            }
        }
    }

}

void MeasurementsManage::addTimeline(QString dId, int chId, QTime startT, QTime endT)
{
    QLabel *deviceId = new QLabel(dId+" ch:"+QString::number(chId));
    Timeline *timeline = new Timeline(nullptr,dId,chId,startT,endT);
    timelineList->append(timeline);
    timelineLabelList->append(deviceId);

}

void MeasurementsManage::addMeasurement(int ver, long dOffset, QList<double> fCarriers, double fSampling, QString sType, QString sFormat,
                                   int cIndex, QString dId, int sShift, long sAmount, int fileNr, QDate dat, QTime tLocal, QList<QString> comm)
{
    Measurement *measurement = new Measurement();
    measurement->addParameters(ver,dOffset,fCarriers,fSampling,sType,sFormat,cIndex,dId,sShift,sAmount,fileNr,dat,tLocal,comm);
    measurementList->append(measurement);
}
