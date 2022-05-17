#include "devicelist.h"
#include <QMessageBox>

DeviceList::DeviceList()
{
    confList = new QComboBox();
    confFile = QDir::currentPath() + "/copy.bat";

    readConf(confFile);

    QPushButton *ok = new QPushButton("OK");
    QPushButton *cancel = new QPushButton("Cancel");
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(ok);
    hLayout->addWidget(cancel);

    vLayout->addWidget(confList);
    vLayout->addLayout(hLayout);

    for(int i=0;i<confDir.size();i++){
        confList->addItem(confDir.at(i));
    }

    setLayout(vLayout);

    QObject::connect(confList, SIGNAL(textActivated(QString)), this, SLOT(setCurrentConf(QString)));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(import()));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    if(!confDir.isEmpty())
        emit confList->textActivated(confList->currentText());

}

void DeviceList::setCurrentConf(const QString cConf)
{
    currentConf = cConf;
}

void DeviceList::readConf(const QString &confFile)
{
    confDir.clear();
    QFile file(confFile);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(confFile), file.errorString()));
        return;
    }
    QString line;
    QTextStream in(&file);
    while(!in.atEnd()){
        line = in.readLine();
        if(line.indexOf("CONF_NAME")>=0)
        {
            line = line.mid(line.indexOf('"')+1);
            line = line.left(line.indexOf('"'));
            confDir.append(line);
        }
        if((line.indexOf("LOCAL_DIR")>=0) & (temporaryFolderPath.size()==0))
        {
            line = line.mid(line.indexOf('"')+1);
            line = line.left(line.indexOf('"'));
            temporaryFolderPath=line;
        }
    }
}

void DeviceList::emittingSent(QString path)
{
    emit configSent(path);
}

void DeviceList::import()
{
    QString arg=currentConf.left(currentConf.indexOf('#'));
    QString cmd = "start cmd.exe @cmd /k "+ confFile + ' ' + arg.toUtf8();
    exec(cmd.toUtf8());
    QDir dir = QDir(temporaryFolderPath);
    if(!dir.exists())
        QMessageBox::warning(this, tr("Transfer Error"),
                            tr("Cannot copy directory from remote device"));
    QFileInfoList list = dir.entryInfoList();
    if(!list.isEmpty()){
        emit configSent(dir.path());
//        dir.removeRecursively();
    }
}

QString DeviceList::exec(const char* cmd)
{
    char buffer[128];
    QString result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");

    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;

        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
