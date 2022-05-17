#ifndef LOADDIR_H
#define LOADDIR_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "measurement.h"

class LoadDir
{

public:
    LoadDir();

public slots:
    QList<Measurement *> *loadDir(const QString &fileName);

protected:
    QList<QString> usedFiles;
    QString dirPath;
    QList <Measurement*> *mList;

private:
    Measurement* loadFile(const QString &filePath, const QString &fileName);


};

#endif // LOADDIR_H
