#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets>
#include "centralwidget.h"
#include "devicelist.h"
#include "loaddir.h"
#include "dirtree.h"

class MainWindow : public QMainWindow, public LoadDir
{
    Q_OBJECT

public:
    MainWindow();
//    void loadFile(const QString &filePath, const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void clear();
    void download();
    void zoom();
    void zoomOut();
//    std::string exec(const char* cmd);
//    void setCurrentConf(const QString cConf);

public slots:
//    void import(QString currentConf, QString conFile, QString temporaryFolderPath);
    void loadRemoteDir(const QString &fileName);

signals:

private:
    void createStatusBar();
    void createActions();
    void createDockWindows();
    void readSettings();
    void writeSettings();
//    void readConf(const QString &confFile);
    CentralWidget *centralWidget;

//    QList<QString> usedFiles;
    DeviceList *deviceList;
    DirTree *dirTree;
    QTextEdit *screen;
//    QList<QString> confDir;
//    QString currentConf;
//    QString confFile = QDir::currentPath() + "/copy.bat";
//    QString temporaryFolderPath;
//    QWidget confWindow;
//    QComboBox *confList;


};


#endif
