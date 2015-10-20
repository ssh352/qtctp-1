todo
======
自动累加计算m1/m5，并加入ringbuffer/db。
加入网络订阅服务。
加入合约详细信息：id+ id- id=

类
======
CtpMgr MdSm TdSm：
ctp状态机和spi实现，接收回调。
内部使用ctpcmdmgr执行命令。
收到的数据写给datapump。
信号：合约列表

CtpCmdMgr CtpCmd:
ctp命令队列，间隔100毫秒取命令执行，如果被流控下一次继续执行。

DataPump LevelDBBackend：
数据接收器，为tick提供长度为256的ringbuffer的缓冲。
分合约自动保存到硬盘。
开始订阅数据之前，自动从数据库加载最近的256项数据到ringbuffer。

信号：tick

Profile Logger ServiceMgr:
配置 日志/崩溃收集 服务管理。

编译
======
系统：win7 sp1 x64
编译器：vs2013 update4 x86
依赖：
Qt5.5.1
Win32OpenSSL-1_0_1p.exe

QT配置
======
shared:
configure -prefix "c:\qtlite\qt5.5-vs12-shared" -confirm-license -opensource -debug-and-release -shared -target xp -accessibility -nomake tests -nomake examples -no-compile-examples -c++11 -ltcg -qt-sql-sqlite -plugin-sql-sqlite -no-freetype -no-opengl -no-qml-debug -no-icu -no-angle -openssl -I "C:\OpenSSL-Win32\include" -qt-zlib -qt-libpng -qt-libjpeg -no-dbus -no-audio-backend -no-wmf-backend -no-style-fusion -force-debug-info -mp -platform win32-msvc2013

static:
configure -prefix "c:\qtlite\qt5.5-vs12-static" -confirm-license -opensource -debug-and-release -static -static-runtime -target xp -accessibility -nomake tests -nomake examples -no-compile-examples -c++11 -ltcg -qt-sql-sqlite -plugin-sql-sqlite -no-freetype -no-opengl -no-qml-debug -no-icu -no-angle -openssl-linked -I "C:\OpenSSL-Win32\include" OPENSSL_LIBS_DEBUG="C:\OpenSSL-Win32\lib\VC\static\ssleay32MTd.lib C:\OpenSSL-Win32\lib\VC\static\libeay32MTd.lib" OPENSSL_LIBS_RELEASE="C:\OpenSSL-Win32\lib\VC\static\ssleay32MT.lib C:\OpenSSL-Win32\lib\VC\static\libeay32MT.lib" -qt-zlib -qt-libpng -qt-libjpeg -no-dbus -no-audio-backend -no-wmf-backend -no-style-fusion -force-debug-info -mp -platform win32-msvc2013

qt.pro:
addModule(qtbase)
addModule(qttools, qtbase)
addModule(qtwebsockets, qtbase)
addModule(qtscript, qtbase, qttools)
addModule(qtwinextras, qtbase)
addModule(qtactiveqt, qtbase)
