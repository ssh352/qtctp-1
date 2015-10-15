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
    aboutdialog.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    configdialog.h \
    aboutdialog.h \
    logindialog.h

FORMS    += mainwindow.ui \
    configdialog.ui \
    aboutdialog.ui \
    logindialog.ui

include(../ctpsdk.pri)
include(../leveldb.pri)
include(../qleveldb.pri)
