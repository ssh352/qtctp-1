SOURCE_DIR = $$PWD/qleveldb

INCLUDEPATH += \
    $$SOURCE_DIR/include \
    $$SOURCE_DIR
    
HEADERS += \
    $$SOURCE_DIR/qleveldb.h \
    $$SOURCE_DIR/qleveldbbatch.h \
    $$SOURCE_DIR/qleveldboptions.h \
    $$SOURCE_DIR/qleveldbglobal.h \

SOURCES += \
    $$SOURCE_DIR/qleveldb.cpp \
    $$SOURCE_DIR/qleveldbbatch.cpp \
    $$SOURCE_DIR/qleveldboptions.cpp \
    $$SOURCE_DIR/qleveldbglobal.cpp \
