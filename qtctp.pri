# warn
win32-msvc*:QMAKE_CXXFLAGS_WARN_ON -= -w34100
win32-msvc*:QMAKE_CXXFLAGS += -wd4819 -wd4267 -wd4244
win32-msvc*:QMAKE_CFLAGS_WARN_ON -= -w34100
win32-msvc*:QMAKE_CFLAGS += -wd4819 -wd4267 -wd4244

# pdb
win32-msvc*:QMAKE_CFLAGS_RELEASE += -Zi
win32-msvc*:QMAKE_CXXFLAGS_RELEASE += -Zi
win32-msvc*:QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF

# posttheadmessage
win32:LIBS += user32.lib
