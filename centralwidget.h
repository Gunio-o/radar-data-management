#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QTimeEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QTextEdit>
#include "loaddir.h"
#include "measurementsmanage.h"

class CentralWidget : public QWidget, public MeasurementsManage
{
    Q_OBJECT
public:
    CentralWidget(QWidget *parent = nullptr);
    virtual ~CentralWidget() {};
//    void createTimelines();
    void addZoomedMeasurements();
//    void addTimeline(QString dId, int chId, QTime startT, QTime endT);
//    void addMeasurement(int ver, long dOffset, QList<double> fCarriers, double fSampling, QString sType, QString sFormat,
//                        int cIndex, QString dId, int sShift, long sAmount, int fileNr, QDate dat, QTime tLocal, QList<QString> comm);
    void setMeasurementList (QList<Measurement*> *mList);
    void setTimelines();
    void setTimeEdit(QPoint start, QPoint end);
    void setZoom();
    void clear();
    void clearAll();
    void showTimelines();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent*);

private:
    QHBoxLayout* createHead();
    QHBoxLayout *mainLayout;
    QVBoxLayout *timelineLayout;
    QGridLayout *timelineAndLabelsLayout;
    QFrame *timelineFrame;
//    QTextEdit *screen;

    QPushButton *button;
//    QCheckBox *zaznaczWszystkie;
    QLabel *startTimeLabel;
    QLabel *endTimeLabel;
    QTimeEdit *startTimeEdit;
    QTimeEdit *endTimeEdit;

//    QList<Timeline*> *timelineList;
//    QList<Measurement*> *measurementList;

    bool zoomed=false;
    QList<Measurement*> *zoomedMeasurementList;



    QPoint dragStartPosition;
    QPoint dragPosition;
    QPoint dragEndPosition;
    QRect mouseMarking;

public slots:
    void buttonClick();
    void selectedMeasurements();

signals:
    void sentText(QString);
};

#endif // CENTRALWIDGET_H
