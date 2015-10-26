#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T12:46:33
#
#-------------------------------------------------

QT       += core gui script scripttools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtstrategy
TEMPLATE = app

include(../qtctp.pri)

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    crashhandler.cpp \
    logger.cpp \
    profile.cpp \
    servicemgr.cpp \
    utils.cpp \
    scriptmgr.cpp

HEADERS  += ui/mainwindow.h \
    crashhandler.h \
    logger.h \
    profile.h \
    servicemgr.h \
    utils.h \
    scriptmgr.h

FORMS    += ui/mainwindow.ui

include(../breakpad.pri)
include(../mhook.pri)

RESOURCES += \
    systray.qrc \
    helloscript.qrc
