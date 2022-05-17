#include "loaddir.h"

LoadDir::LoadDir()
{
    mList = new QList <Measurement*>;
}

QList <Measurement*>* LoadDir::loadDir(const QString &dir)
{
    QDir directory(dir);
    directory.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList list = directory.entryInfoList();

    for (int i = 0; i<list.size() ; i++) {
        if(!(usedFiles.contains(list.at(i).fileName())))
        {
            if((list.at(i).isFile()) & (list.at(i).fileName().right(4) == ".usf"))
            {
                usedFiles.append(list.at(i).fileName());
                mList->append(loadFile(list.at(i).filePath(),list.at(i).fileName()));
            }
            if(list.at(i).isDir())
            {
                loadDir(list.at(i).filePath());
            }
        }
    }

    directory.cdUp();
    dirPath = directory.path();
    return mList;

}

Measurement* LoadDir::loadFile(const QString &filePath, const QString &fileName)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {

        return nullptr;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    QString jsonFile=in.readLine();
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFile.toUtf8());

            int version = jsonDocument["version"].toInt();
            long dataOffset =jsonDocument["dataOffset"].toInt();

            QJsonArray fCarriers = jsonDocument["parameters"]["frequencyCarriers"].toArray();
            QList<double> frequencyCarriers;
            for (int i=0;i<fCarriers.size();i++) {
                frequencyCarriers.append(fCarriers.at(i).toDouble());
            }
            double frequencySampling = jsonDocument["parameters"]["frequencySampling"].toDouble();

            QString sampleType = jsonDocument["parameters"]["sampleType"].toString();
            QString sampleFormat = jsonDocument["parameters"]["sampleFormat"].toString();

            QString deviceId =fileName.left(fileName.indexOf('_'));

            int channelIndex = jsonDocument["parameters"]["channelIndex"].toInt();

            int samplesShift = jsonDocument["parameters"]["samplesShift"].toInt();
            long samplesAmount = jsonDocument["parameters"]["samplesAmount"].toInt();
            int fileNumber = jsonDocument["parameters"]["fileNumber"].toInt();

            QString fileTimestampLocal = jsonDocument["parameters"]["fileTimestamp"]["local"].toString().remove(24,8);
            QDate date = QDate::fromString(fileTimestampLocal.left(10),"yyyy-MM-dd");
            QTime timestampLocal = QTime::fromString(fileTimestampLocal.right(12),"hh-mm-ss-zzz");

            QJsonArray comm = jsonDocument["comments"].toArray();
            QList<QString> comments;
            for (int i=0;i<comm.size();i++) {
                comments.append(comm.at(i).toString());
            }

            Measurement *measurement = new Measurement();
            measurement->addParameters(version,dataOffset,frequencyCarriers,frequencySampling,sampleType,sampleFormat,channelIndex,
                                          deviceId,samplesShift,samplesAmount,fileNumber,date,timestampLocal,comments);
            return measurement;

}
