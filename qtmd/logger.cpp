#include "logger.h"
#include "CrashHandler.h"
#include "profile.h"

#include <QDir>
#include <QCoreApplication>
#include <crtdbg.h>
#include <windows.h>
#include <QtGlobal>
#include <QTime>

static QtMessageHandler preMessageHandler = nullptr;

static void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
#ifndef _DEBUG
    if (type == QtFatalMsg){
        __debugbreak();
    }
#endif
    preMessageHandler(type,context,msg);
}

Logger::Logger(QObject* parent)
    : QObject(parent)
{
}

void Logger::init()
{
#ifndef _DEBUG
    // Disable the message box for assertions.(see setcrt)
    _CrtSetReportMode(_CRT_ASSERT, 0);

    // Preserve existing error mode, as discussed at http://t/dmea
    UINT new_flags = SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX;
    UINT existing_flags = SetErrorMode(new_flags);
    SetErrorMode(existing_flags | new_flags);
#endif

    QString reporter = "C:/Program Files (x86)/Windows Kits/8.0/Debuggers/x86/windbg.exe";
    QString params = " -z";
    if (!QDir().exists(reporter)) {
        reporter = "c:/windows/system32/notepad.exe";
        params = "";
    }
    CrashManager::CrashHandler::instance()->Init(qApp->applicationDirPath(), reporter, params);

    preMessageHandler = qInstallMessageHandler(myMessageHandler);

    log_.setFileName(Profile::logPath());
    log_.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append|QIODevice::Unbuffered);
}

void Logger::shutdown()
{
    log_.close();
}

void Logger::info(QString msg){
    QString log = QTime::currentTime().toString("hh:mm:ss.zzz==>") + msg;
    QString logToFile = log + QStringLiteral("\n");

    // write to file
    mutex_.lock();
    log_.write(logToFile.toUtf8().constData());
    log_.flush();
    mutex_.unlock();

    // dispatch...
    emit gotInfo(log);
}
