#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class DeviceList : public QWidget
{
    Q_OBJECT
public:
    DeviceList();

protected:
    void readConf(const QString &confFile);

private slots:
    void setCurrentConf(const QString cConf);
    void emittingSent(QString path);
    void import();


signals:
    void configSent(QString);

private:
    QString exec(const char* cmd);
    QList<QString> confDir;
    QString currentConf;
    QString confFile;
    QString temporaryFolderPath;
    QComboBox *confList;
};

#endif // DEVICELIST_H
