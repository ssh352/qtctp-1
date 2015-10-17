#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T13:26:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mdsrv
TEMPLATE = app

win32-msvc*:QMAKE_CXXFLAGS_WARN_ON -= -w34100
win32-msvc*:QMAKE_CXXFLAGS += -wd4819

SOURCES += main.cpp\
    mainwindow.cpp \
    configdialog.cpp \
    logindialog.cpp \
    tickform.cpp \
    servicemgr.cpp \
    profile.cpp

HEADERS  += mainwindow.h \
    configdialog.h \
    logindialog.h \
    tickform.h \
    servicemgr.h \
    profile.h

FORMS    += mainwindow.ui \
    configdialog.ui \
    logindialog.ui \
    tickform.ui

include(../ctpsdk.pri)
include(../leveldb.pri)
include(../qleveldb.pri)

RESOURCES += \
    systray.qrc
