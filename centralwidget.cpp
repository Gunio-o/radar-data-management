#include "centralwidget.h"



CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    zoomedMeasurementList = new QList<Measurement*>();
    timelineFrame = new QFrame();
    timelineFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timelineFrame->setLineWidth(2);

    timelineLayout = new  QVBoxLayout();
    timelineLayout->setDirection(QBoxLayout::BottomToTop);
    timelineLayout->addStretch(1);

    timelineAndLabelsLayout = new QGridLayout();
    timelineAndLabelsLayout->setColumnStretch(1,0);
    timelineAndLabelsLayout->setColumnStretch(2,1);

    button = new QPushButton("Zobacz zdarzenia");
    timelineLayout->addWidget(button);

    QHBoxLayout *timeEditLayout = new QHBoxLayout();
    startTimeEdit = new QTimeEdit(QTime(0,0));
    startTimeEdit->setDisplayFormat("hh:mm:ss.zzz");
    endTimeEdit = new QTimeEdit(QTime(23,59));
    endTimeEdit->setDisplayFormat("hh:mm:ss.zzz");

    timeEditLayout->addWidget(startTimeEdit,0,Qt::AlignLeft);
    timeEditLayout->addWidget(endTimeEdit,0,Qt::AlignRight);
    timelineLayout->addLayout(timeEditLayout);
    timelineLayout->addLayout(timelineAndLabelsLayout);
    timelineLayout->addSpacing(10);


    QVBoxLayout *layout = new  QVBoxLayout();
    layout->addLayout(createHead(),0);
    layout->addLayout(timelineLayout,1);
    timelineFrame->setLayout(layout);

    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(timelineFrame,5);

    setLayout(mainLayout);
    repaint();
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(buttonClick()));
    QObject::connect(startTimeEdit, SIGNAL(timeChanged(QTime)), this, SLOT(selectedMeasurements()));
    QObject::connect(endTimeEdit, SIGNAL(timeChanged(QTime)), this, SLOT(selectedMeasurements()));
}

QHBoxLayout* CentralWidget::createHead()
{
    QVBoxLayout *headDescryptionLayout = new QVBoxLayout();
    headDescryptionLayout->addWidget(new QLabel("stanowiska:"));

    QHBoxLayout *timelineEnds = new QHBoxLayout();
    startTimeLabel = new QLabel("00:00:00");
    endTimeLabel = new QLabel("23:59:00");
    timelineEnds->addWidget(startTimeLabel,0,Qt::AlignLeft);
    timelineEnds->addWidget(endTimeLabel,0,Qt::AlignRight);

    QHBoxLayout *headLayout = new QHBoxLayout();
    headLayout->addLayout(headDescryptionLayout,0);
    headLayout->addLayout(timelineEnds,1);


    return headLayout;
}

void CentralWidget::setMeasurementList (QList<Measurement*> *mList)
{
    for (int i=0;i<mList->size();i++) {
        measurementList->append(mList->at(i));
    }

}

void CentralWidget::setTimeEdit(QPoint start, QPoint end)
{
    if(!timelineList->isEmpty()){
        double duration=timelineList->last()->getDuration();
        double mSecond = duration/timelineList->last()->width();
        double sTime = (start.x() - (timelineFrame->pos().rx() + timelineList->last()->pos().rx())) * mSecond;
        double eTime = (end.x() - (timelineFrame->pos().rx() + timelineList->last()->pos().rx())) * mSecond;
        double s;

        if(sTime>eTime){
            s=sTime;
            sTime=eTime;
            eTime=s;

        }

        if(sTime>=0){
            startTimeEdit->setTime(timelineList->last()->getStartTime().addMSecs(sTime));}
        else{
            startTimeEdit->setTime(timelineList->last()->getStartTime());}

        if(eTime<=duration){
            endTimeEdit->setTime(timelineList->last()->getStartTime().addMSecs(eTime));}
        else{
            endTimeEdit->setTime(timelineList->last()->getStartTime().addMSecs(duration));}
    }

}

void CentralWidget::addZoomedMeasurements()
{
    clear();
    for (int i=0; i<measurementList->size(); i++) {
        if(measurementList->at(i)->isSelected())
            zoomedMeasurementList->append(measurementList->at(i));
    }

}

void CentralWidget::clearAll()
{
    qDebug()<<measurementList->size();
    clear();
    measurementList->clear();
    qDebug()<<measurementList->size();

}

void CentralWidget::clear()
{
    for (int i=0;i<timelineList->size();i++) {
        timelineAndLabelsLayout->removeWidget(timelineList->at(i));
        timelineAndLabelsLayout->removeWidget(timelineLabelList->at(i));
        timelineList->at(i)->setGeometry(-50,-50,0,0);
        timelineList->at(i)->erase();
        timelineLabelList->at(i)->setGeometry(-50,-50,0,0);
        timelineLabelList->at(i)->setText("");


    }
    timelineList->clear();
    timelineLabelList->clear();
    zoomedMeasurementList->clear();

}

void CentralWidget::setTimelines()
{
    clear();
    createTimelines(measurementList);
    showTimelines();
}

void CentralWidget::showTimelines()
{
    startTimeLabel->setText(startTime.toString("hh:mm:ss:zzz"));
    endTimeLabel->setText(endTime.toString("hh:mm:ss:zzz"));
    QString dId;
    int cIndex;
    for (int i=0; i<timelineList->size(); i++){
        dId = timelineList->at(i)->getDeviceId();
        cIndex = timelineList->at(i)->getChannelIndex();
        QLabel *deviceId = new QLabel(dId+" ch:"+QString::number(cIndex));
        timelineLabelList->append(deviceId);
        timelineAndLabelsLayout->addWidget(timelineLabelList->at(i),i,1);
        timelineAndLabelsLayout->addWidget(timelineList->at(i),i,2);

        timelineLayout->addSpacing(0);
    }
}


void CentralWidget::setZoom()
{
    zoomed = true;
}

void CentralWidget::selectedMeasurements()
{
    long sTime = 0;
    long dTime = 0;
    if(!measurementList->isEmpty()){
        for(int i=0;i<measurementList->size();i++){
            sTime = measurementList->at(i)->getTimestamp();
            dTime = measurementList->at(i)->getDuration() + sTime;
            if(sTime>=startTimeEdit->time().msecsSinceStartOfDay() &&
                    dTime<=endTimeEdit->time().msecsSinceStartOfDay())
            {
                measurementList->at(i)->setSelected();
            }
            else
                measurementList->at(i)->setUnselected();
        }
        for (int j=0;j<timelineList->size();j++) {
            timelineList->at(j)->repaint();
        }
    }
}


void CentralWidget::buttonClick()
{
    QString text = "";
    QString measureText;
    if(startTimeEdit->time()<=endTimeEdit->time()){
        if(!measurementList->isEmpty()){
            for(int i=0;i<measurementList->size();i++){
                if(measurementList->at(i)->isSelected())
                {
                    measureText="";
                    measureText.append("Time: " + measurementList->at(i)->getStartTime().toString()+"\n");
                    if(measurementList->at(i)->getComments()!="")
                        measureText.append("comment: " + measurementList->at(i)->getComments() + "\n");
                    else
                        measureText.append("comment: no comment\n");
                    measureText.append('\n');
                    if(text.indexOf(measureText)<0){
                        text.append(measureText);}
                }
            }
        }
        else{
            text = "brak pomiarów";
        }
    }
    else{
        text = "czas startowy większy od koncowego";
    }
    emit sentText(text);
}


void CentralWidget::mousePressEvent(QMouseEvent *event)
{
    dragStartPosition = event->pos();
    dragPosition = event->pos();
    repaint();
}

void CentralWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
            return;
    dragPosition = event->pos();
    repaint();
    setTimeEdit(dragStartPosition,dragPosition);
    selectedMeasurements();


}

void CentralWidget::mouseReleaseEvent(QMouseEvent *event)
{


    dragEndPosition = event->pos();

    setTimeEdit(dragStartPosition,dragEndPosition);

    if(zoomed){
        clear();
        addZoomedMeasurements();
        createTimelines(zoomedMeasurementList);
        showTimelines();
        zoomed = false;
    }

    dragStartPosition = QPoint(-50,-50);
    dragPosition = QPoint(-50,-50);
    repaint();
}

void CentralWidget::paintEvent(QPaintEvent *event)
{

    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);
    paint.setCompositionMode(QPainter::CompositionMode_SourceOver);

    paint.setBrush(QColor(0,0,255,50));
    QPen pen;
    pen.setWidth(1);
    pen.setBrush(QColor(0,0,100,100));
    paint.setPen(pen);
    mouseMarking.setTopLeft(dragStartPosition);
    mouseMarking.setBottomRight(dragPosition);
    paint.drawRect(mouseMarking);

}
