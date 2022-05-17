#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QFrame>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>
#include <QTime>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>

QT_BEGIN_NAMESPACE
class Measurement;
QT_END_NAMESPACE

class Timeline : public QWidget
{
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = nullptr, QString dId=0, int chId=0, QTime startT=QTime(0,0), QTime endT=QTime(23,59));
    void addMeasurement(Measurement* measure);
    double long getDuration();
    QTime getStartTime();
    QString getDeviceId();
    int getChannelIndex();

    void erase();
    bool isErase();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);


private:
    int channelIndex;
    QString deviceId;
    QTime startTime;
    QTime endTime;
    double long czRozpoczecia;
    double long czZakonczenia;
    double long duration;
//    double szerokosc;
    QList<Measurement*> *measurementList;

    bool toErase = false;

signals:
    void zmianaRozmiaru(double szer);
    void szerokoscPomiaru(double);

};

#endif // TIMELINE_H
