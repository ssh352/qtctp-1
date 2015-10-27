todo
======
简化设计，分为历史服务和实时服务。
历史服务采用jsonrpc，提供读取tick和bar。
实时服务采用tcpstream推送tick，每次链接上全推当天的tick/数据库里面的所有tick。
数据库分为历史数据库和当天的数据库。
每天下午5点开始做收盘处理，当天数据库数据导入历史数据库并计算bar和ta。
ringbuffer其实可以不要，直接leveldb来缓存完成读写推就可以了，为了界面显示先保留。

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
信号：tick
数据格式：
合约定位：id+ id=
合约查询：id-xxxx
tick定位：tick-id+ tick-id=
tick查询：tick-id-xxxx

Profile Logger ServiceMgr:
配置 日志/崩溃收集 服务管理。

编译
======
系统：win7 sp1 x64
编译器：vs2013 update4 x64
依赖：
Qt5.5.1 x64
v6.3.6_20150515_traderapi_win64.zip
Win64OpenSSL-1_0_2d.exe
mhook-2.4.zip
leveldb 1.18
qwt-6.1.2.zip
QCustomPlot 1.3.1
google breakpad

QT配置
======
x64-shared:
configure -prefix "c:\qtlite\qt5.5-vs12-shared-x64" -confirm-license -opensource -debug-and-release -shared -accessibility -nomake tests -nomake examples -no-compile-examples -c++11 -ltcg -qt-sql-sqlite -plugin-sql-sqlite -no-freetype -no-opengl -no-qml-debug -no-icu -no-angle -openssl -I "C:\OpenSSL-Win64\include" -qt-zlib -qt-libpng -qt-libjpeg -no-dbus -no-audio-backend -no-wmf-backend -no-style-fusion -force-debug-info -mp -platform win32-msvc2013
x64-static:
configure -prefix "c:\qtlite\qt5.5-vs12-static-x64" -confirm-license -opensource -debug-and-release -static -static-runtime -accessibility -nomake tests -nomake examples -no-compile-examples -c++11 -ltcg -qt-sql-sqlite -plugin-sql-sqlite -no-freetype -no-opengl -no-qml-debug -no-icu -no-angle -openssl-linked -I "C:\OpenSSL-Win64\include" OPENSSL_LIBS_DEBUG="C:\OpenSSL-Win64\lib\VC\static\ssleay32MTd.lib C:\OpenSSL-Win64\lib\VC\static\libeay32MTd.lib" OPENSSL_LIBS_RELEASE="C:\OpenSSL-Win64\lib\VC\static\ssleay32MT.lib C:\OpenSSL-Win64\lib\VC\static\libeay32MT.lib" -qt-zlib -qt-libpng -qt-libjpeg -no-dbus -no-audio-backend -no-wmf-backend -no-style-fusion -force-debug-info -mp -platform win32-msvc2013
x86-shared:
configure -prefix "c:\qtlite\qt5.5-vs12-shared" -confirm-license -opensource -debug-and-release -shared -target xp -accessibility -nomake tests -nomake examples -no-compile-examples -c++11 -ltcg -qt-sql-sqlite -plugin-sql-sqlite -no-freetype -no-opengl -no-qml-debug -no-icu -no-angle -openssl -I "C:\OpenSSL-Win32\include" -qt-zlib -qt-libpng -qt-libjpeg -no-dbus -no-audio-backend -no-wmf-backend -no-style-fusion -force-debug-info -mp -platform win32-msvc2013
x86-static:
configure -prefix "c:\qtlite\qt5.5-vs12-static" -confirm-license -opensource -debug-and-release -static -static-runtime -target xp -accessibility -nomake tests -nomake examples -no-compile-examples -c++11 -ltcg -qt-sql-sqlite -plugin-sql-sqlite -no-freetype -no-opengl -no-qml-debug -no-icu -no-angle -openssl-linked -I "C:\OpenSSL-Win32\include" OPENSSL_LIBS_DEBUG="C:\OpenSSL-Win32\lib\VC\static\ssleay32MTd.lib C:\OpenSSL-Win32\lib\VC\static\libeay32MTd.lib" OPENSSL_LIBS_RELEASE="C:\OpenSSL-Win32\lib\VC\static\ssleay32MT.lib C:\OpenSSL-Win32\lib\VC\static\libeay32MT.lib" -qt-zlib -qt-libpng -qt-libjpeg -no-dbus -no-audio-backend -no-wmf-backend -no-style-fusion -force-debug-info -mp -platform win32-msvc2013

qt.pro:
addModule(qtbase)
addModule(qttools, qtbase)
addModule(qtwebsockets, qtbase)
addModule(qtscript, qtbase, qttools)
addModule(qtwinextras, qtbase)
addModule(qtactiveqt, qtbase)
