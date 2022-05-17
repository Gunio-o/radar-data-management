#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QProcess>
#include <QDir>

#include "mainwindow.h"



int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("ISE");
    QCoreApplication::setApplicationName("Aplikacja do obslugi danych pomiarowych");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    MainWindow mainWin;
    mainWin.show();
    return app.exec();

}

