SOURCE_DIR = $$PWD/ctpsdk
INCLUDEPATH += \
    $$SOURCE_DIR/include \
    $$SOURCE_DIR

SOURCES += \
    $$SOURCE_DIR/mdapi_proxy.cpp \
    $$SOURCE_DIR/tdapi_proxy.cpp \
    $$SOURCE_DIR/sdk_utils.cpp \

HEADERS += \
    $$SOURCE_DIR/ApiDataType.h \
    $$SOURCE_DIR/ApiStruct.h \
    $$SOURCE_DIR/MdApi.h \
    $$SOURCE_DIR/TraderApi.h \
    $$SOURCE_DIR/sdk_utils.h \

contains(QT_ARCH, i386) {
    #message("32-bit")
    RESOURCES += \
        $$SOURCE_DIR/ctpsdk_bin.qrc
} else {
    #message("64-bit")
    RESOURCES += \
        $$SOURCE_DIR/ctpsdk_bin_x64.qrc
}
