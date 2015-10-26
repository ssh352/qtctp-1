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
    profile.cpp \
    servicemgr.cpp \
    scriptmgr.cpp

HEADERS  += ui/mainwindow.h \
    profile.h \
    servicemgr.h \
    scriptmgr.h

FORMS    += ui/mainwindow.ui

include(../breakpad.pri)
include(../mhook.pri)
include(../utils.pri)

RESOURCES += \
    systray.qrc \
    helloscript.qrc
