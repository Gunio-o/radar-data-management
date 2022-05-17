#include "timeline.h"
#include "measurement.h"

Timeline::Timeline(QWidget *parent, QString dId, int chId, QTime startT, QTime endT) : QWidget(parent)
{
    measurementList = new QList<Measurement*>;
    this->setFixedHeight(20);
    this->setMinimumWidth(150);

    deviceId = dId;
    channelIndex = chId;
    startTime = startT;
    endTime = endT;
    czRozpoczecia = startTime.msecsSinceStartOfDay();
    czZakonczenia = endTime.msecsSinceStartOfDay();
    duration = czZakonczenia - czRozpoczecia;
}


void Timeline::addMeasurement(Measurement *measure)
{
    measurementList->append(measure);
    measurementList->last()->setParent(this);
}

double long Timeline::getDuration()
{
    return duration;
}

QTime Timeline::getStartTime()
{
    return startTime;
}

QString Timeline::getDeviceId()
{
    return deviceId;
}

int Timeline::getChannelIndex()
{
    return channelIndex;
}

void Timeline::erase()
{
    toErase = true;
}

bool Timeline::isErase()
{
    return toErase;
}

void Timeline::resizeEvent(QResizeEvent *event)
{
//    double pozycjaX=0;
//    double pozycjaSzer=0;
//    int szerokosc = event->size().width();
//    for(int i=0;i<measurementList->size();i++){
//        double czasRozp = measurementList->at(i)->getTimestamp();
//        double czasTrw = measurementList->at(i)->getDuration();
//        pozycjaX = czasRozp*szerokosc/duration+frameWidth();
//        pozycjaSzer = czasTrw*szerokosc/duration;
//        measurementList->at(i)->setGeometry(pozycjaX,frameWidth(),pozycjaSzer,20-2*frameWidth());
//        measurementList->at(i)->setStyleSheet("background-color: rgb(255,255,0)");
//    }
//    emit zmianaRozmiaru(szerokosc);
//    emit szerokoscPomiaru(pozycjaX+pozycjaSzer);
}

void Timeline::paintEvent(QPaintEvent *event)
{
    double pozycjaX=0;
    double pozycjaSzer=0;
    double startT=0;
    double durationT=0;

    QPainter paint(this);
    paint.eraseRect(this->rect());
    paint.setRenderHint(QPainter::Antialiasing);
    paint.setCompositionMode(QPainter::CompositionMode_SourceOver);
    paint.setBrush(QColor(150,0,0));
    QPen pen;
    pen.setWidth(1);
    pen.setBrush(QColor(100,100,0));
    paint.setPen(pen);
    paint.drawRect(0,0,this->width(),this->height());
    paint.setBrush(QColor(255,255,0));

    pen.setWidth(1);
    pen.setBrush(QColor(100,100,0));
    paint.setPen(pen);


    for(int i=0;i<measurementList->size();i++){
        if(measurementList->at(i)->isSelected()){
            paint.setBrush(QColor(0,255,0));}
        else{
            paint.setBrush(QColor(255,255,0));
        }
        startT = measurementList->at(i)->getTimestamp();
        durationT = measurementList->at(i)->getDuration();
        pozycjaX = (startT-czRozpoczecia)*(this->width())/duration;
        pozycjaSzer = durationT*(this->width())/duration;
        if(pozycjaX-int(pozycjaX)>=0.5){
            pozycjaX=(int)pozycjaX+1;}
        if(pozycjaSzer-int(pozycjaSzer)>=0.5){
            pozycjaSzer=(int)pozycjaSzer+1;}
        if(pozycjaSzer-int(pozycjaSzer)+pozycjaX-int(pozycjaX)>=0.5 && pozycjaSzer-int(pozycjaSzer)+pozycjaX-int(pozycjaX)<1){
            pozycjaSzer=(int)pozycjaSzer+1;}
        if((int)pozycjaSzer==0){
            pozycjaSzer=1;
            pen.setWidth(0);
        }
        else {
            pen.setWidth(1);}

        paint.drawRect((int)pozycjaX,0,(int)pozycjaSzer,20);
        measurementList->at(i)->setGeometry((int)pozycjaX,0,(int)pozycjaSzer-1,20);

    }
    paint.setBrush(QColor(255,255,255,0));
    pen.setWidth(1);
    pen.setBrush(QColor(0,0,0,255));
    paint.drawRect(0,0,this->width(),this->height());



}

