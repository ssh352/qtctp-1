#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T12:46:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtdemo
TEMPLATE = app

include(../qtctp.pri)

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    crashhandler.cpp \
    logger.cpp \
    profile.cpp \
    servicemgr.cpp \
    utils.cpp

HEADERS  += ui/mainwindow.h \
    crashhandler.h \
    logger.h \
    profile.h \
    servicemgr.h \
    utils.h

FORMS    += ui/mainwindow.ui

include(../breakpad.pri)

RESOURCES += \
    systray.qrc
