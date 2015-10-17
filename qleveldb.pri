SOURCE_DIR = $$PWD/qleveldb

INCLUDEPATH += \
    $$SOURCE_DIR/include \
    $$SOURCE_DIR
    
HEADERS += \
    $$SOURCE_DIR/qleveldb.h \
    $$SOURCE_DIR/qleveldbbatch.h \
    $$SOURCE_DIR/json_utils.h \

SOURCES += \
    $$SOURCE_DIR/qleveldb.cpp \
    $$SOURCE_DIR/qleveldbbatch.cpp \
    $$SOURCE_DIR/json_utils.cpp \
