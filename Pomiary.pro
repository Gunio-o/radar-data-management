QT += gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        centralwidget.cpp \
        devicelist.cpp \
        dirtree.cpp \
        loaddir.cpp \
        main.cpp \
        mainwindow.cpp \
        measurement.cpp \
        measurementsmanage.cpp \
        timeline.cpp

RESOURCES     = application.qrc
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application

!isEmpty(target.path): INSTALLS += target

HEADERS += \
    centralwidget.h \
    devicelist.h \
    dirtree.h \
    loaddir.h \
    mainwindow.h \
    measurement.h \
    measurementsmanage.h \
    timeline.h

QT += widgets
