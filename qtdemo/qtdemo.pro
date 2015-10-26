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
    profile.cpp \
    servicemgr.cpp

HEADERS  += ui/mainwindow.h \
    profile.h \
    servicemgr.h

FORMS    += ui/mainwindow.ui

include(../breakpad.pri)
include(../mhook.pri)
include(../utils.pri)

RESOURCES += \
    systray.qrc
