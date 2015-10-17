SOURCE_DIR = $$PWD/ctpsdk
INCLUDEPATH += \
    $$SOURCE_DIR/include \
    $$SOURCE_DIR

SOURCES += \
    $$SOURCE_DIR/mdapi_proxy.cpp \
    $$SOURCE_DIR/tdapi_proxy.cpp \
    $$SOURCE_DIR/utils.cpp \
    $$SOURCE_DIR/mdsm.cpp \
    $$SOURCE_DIR/tdsm.cpp \
    $$PWD/ctpsdk/ctpcmd.cpp \
    $$PWD/ctpsdk/ringbuffer.cpp

HEADERS += \
    $$SOURCE_DIR/ApiDataType.h \
    $$SOURCE_DIR/ApiStruct.h \
    $$SOURCE_DIR/MdApi.h \
    $$SOURCE_DIR/TraderApi.h \
    $$SOURCE_DIR/utils.h \
    $$SOURCE_DIR/mdsm.h \
    $$SOURCE_DIR/tdsm.h \
    $$PWD/ctpsdk/ctpcmd.h \
    $$PWD/ctpsdk/ringbuffer.h

RESOURCES += \
    $$SOURCE_DIR/ctpsdk_bin.qrc
