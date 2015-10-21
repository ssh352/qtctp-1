#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T13:26:03
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtmd
TEMPLATE = app

# warn
win32-msvc*:QMAKE_CXXFLAGS_WARN_ON -= -w34100
win32-msvc*:QMAKE_CXXFLAGS += -wd4819

# pdb
win32-msvc*:QMAKE_CFLAGS_RELEASE += -Zi
win32-msvc*:QMAKE_CXXFLAGS_RELEASE += -Zi
win32-msvc*:QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF

win32:LIBS += user32.lib

INCLUDEPATH += \
    $$PWD

SOURCES += main.cpp\
    ui/mainwindow.cpp \
    ui/configdialog.cpp \
    ui/logindialog.cpp \
    servicemgr.cpp \
    profile.cpp \
    logger.cpp \
    ctpcmd.cpp \
    mdsm.cpp \
    ringbuffer.cpp \
    tdsm.cpp \
    ctpcmdmgr.cpp \
    ctpmgr.cpp \
    datapump.cpp \
    crashhandler.cpp \
    ui/instrumentsform.cpp \
    ui/historyform.cpp \
    ui/ringbufferform.cpp


HEADERS  += ui/mainwindow.h \
    ui/configdialog.h \
    ui/logindialog.h \
    servicemgr.h \
    profile.h \
    logger.h \
    ctpcmd.h \
    mdsm.h \
    ringbuffer.h \
    tdsm.h \
    ctpcmdmgr.h \
    ctpmgr.h \
    datapump.h \
    crashhandler.h \
    ui/instrumentsform.h \
    ui/historyform.h \
    ui/ringbufferform.h


FORMS    += ui/mainwindow.ui \
    ui/configdialog.ui \
    ui/logindialog.ui \
    ui/instrumentsform.ui \
    ui/historyform.ui \
    ui/ringbufferform.ui

include(../ctpsdk.pri)
include(../leveldb.pri)
include(../breakpad.pri)

RESOURCES += \
    systray.qrc

