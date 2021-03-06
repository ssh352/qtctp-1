#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T13:26:03
#
#-------------------------------------------------

QT       += core gui script websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtmdsrv
TEMPLATE = app

include(../qtctp.pri)

SOURCES += main.cpp\
    ui/mainwindow.cpp \
    ui/configdialog.cpp \
    ui/logindialog.cpp \
    servicemgr.cpp \
    profile.cpp \
    ctpcmd.cpp \
    mdsm.cpp \
    ringbuffer.cpp \
    tdsm.cpp \
    ctpcmdmgr.cpp \
    ctpmgr.cpp \
    datapump.cpp \
    ui/instrumentsform.cpp \
    ui/historyform.cpp \
    ui/ringbufferform.cpp \
    rpcservice.cpp \
    pushservice.cpp \
    ui/mergeform.cpp \
    leveldbbackend.cpp


HEADERS  += ui/mainwindow.h \
    ui/configdialog.h \
    ui/logindialog.h \
    servicemgr.h \
    profile.h \
    ctpcmd.h \
    mdsm.h \
    ringbuffer.h \
    tdsm.h \
    ctpcmdmgr.h \
    ctpmgr.h \
    datapump.h \
    ui/instrumentsform.h \
    ui/historyform.h \
    ui/ringbufferform.h \
    rpcservice.h \
    pushservice.h \
    ui/mergeform.h \
    leveldbbackend.h


FORMS    += ui/mainwindow.ui \
    ui/configdialog.ui \
    ui/logindialog.ui \
    ui/instrumentsform.ui \
    ui/historyform.ui \
    ui/ringbufferform.ui \
    ui/mergeform.ui

include(../ctpsdk.pri)
include(../leveldb.pri)
include(../breakpad.pri)
include(../qjsonrpc.pri)
include(../qcustomplot.pri)
include(../qwt.pri)
include(../mhook.pri)
include(../utils.pri)

RESOURCES += \
    systray.qrc

