#include <QtWidgets>

#include "mainwindow.h"


MainWindow::MainWindow()

{
    deviceList = new DeviceList();
    centralWidget = new CentralWidget();
    setCentralWidget(centralWidget);


    createActions();
    createStatusBar();
    createDockWindows();

    readSettings();

    QObject::connect(deviceList, SIGNAL(configSent(QString)), this, SLOT(loadRemoteDir(QString)));
    QObject::connect(centralWidget, SIGNAL(sentText(QString)), screen, SLOT(setText(QString)));
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon clearIcon = QIcon(":/images/clear.png");
    QAction *clearAct = new QAction(clearIcon, tr("&Clear..."), this);
    clearAct->setShortcuts(QKeySequence::Close);
    clearAct->setStatusTip(tr("Clear all"));
    connect(clearAct, &QAction::triggered, this, &MainWindow::clear);
    fileMenu->addAction(clearAct);
    fileToolBar->addAction(clearAct);

    const QIcon downloadIcon = QIcon(":/images/new.png");
    QAction *downloadAct = new QAction(downloadIcon, tr("&Import..."), this);
    downloadAct->setShortcuts(QKeySequence::Close);
    downloadAct->setStatusTip(tr("Import from remot device"));
    connect(downloadAct, &QAction::triggered, this, &MainWindow::download);
    fileMenu->addAction(downloadAct);
    fileToolBar->addAction(downloadAct);

    QToolBar *zoomToolBar = addToolBar(tr("Edit"));

    const QIcon zoomIcon = QIcon(":/images/zoom.png");
    QAction *zoomAct = new QAction(zoomIcon, tr("&Zoom..."), this);
    zoomAct->setStatusTip(tr("Zoom by time"));
    connect(zoomAct, &QAction::triggered, this, &MainWindow::zoom);
    zoomToolBar->addAction(zoomAct);

    const QIcon zoomOutIcon = QIcon(":/images/zoomOut.png");
    QAction *zoomOutAct = new QAction(zoomOutIcon, tr("&ZoomOut..."), this);
    zoomOutAct->setStatusTip(tr("Zoom"));
    connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);
    zoomToolBar->addAction(zoomOutAct);


}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Directory path"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dirTree = new DirTree(dock);
    dock->setWidget(dirTree);
    dock->setFloating(false);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    dock = new QDockWidget(tr("Screen"), this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    screen = new QTextEdit(dock);
    dock->setWidget(screen);
    dock->setFloating(false);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void MainWindow::open()
{
    QString dir = QFileDialog::getExistingDirectory(this);
    if (!dir.isEmpty())
    {       
        centralWidget->setMeasurementList(loadDir(dir));
        centralWidget->setTimelines();
        dirTree->setPath(dirPath);
    }
    mList->clear();
}

void MainWindow::download()
{
    deviceList->show();
}

void MainWindow::zoom()
{
    centralWidget->setZoom();
}

void MainWindow::zoomOut()
{
    centralWidget->setTimelines();
}

void MainWindow::clear()
{
    usedFiles.clear();
    centralWidget->clearAll();
}
void MainWindow::loadRemoteDir(const QString &dir)
{
        centralWidget->setMeasurementList(loadDir(dir));
        centralWidget->setTimelines();
        dirTree->setPath(dirPath);
        mList->clear();
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect availableGeometry = screen->geometry();
        resize(availableGeometry.width(), availableGeometry.height());
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}


void MainWindow::writeSettings()

{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
}
