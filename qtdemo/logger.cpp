#include "logger.h"
#include "CrashHandler.h"
#include "profile.h"
#include "utils.h"
#include "servicemgr.h"
#include <windows.h>
#include "mhook-lib/mhook.h"

#include <QDir>
#include <QCoreApplication>
#include <crtdbg.h>
#include <windows.h>
#include <QtGlobal>
#include <QTime>

static bool g_stopExitMonitor = false;

static void myExit()
{
    if (!g_stopExitMonitor) {
        g_stopExitMonitor = true;
        base::debug::StackTrace stacktrace;
        base::debug::Alias(&stacktrace);
        CrashManager::CrashHandler::instance()->writeMinidump();
    }
}

typedef VOID(__stdcall* fn_ExitProcess)(UINT uExitCode);
typedef BOOL(__stdcall* fn_TerminateProcess)(HANDLE hProcess, UINT uExitCode);
fn_ExitProcess oldExitProcess = (fn_ExitProcess)::GetProcAddress(::GetModuleHandleW(L"kernel32"), "ExitProcess");
fn_TerminateProcess oldTerminateProcess = (fn_TerminateProcess)::GetProcAddress(::GetModuleHandleW(L"kernel32"), "TerminateProcess");

VOID __stdcall myExitProcess(UINT uExitCode)
{
    if (!g_stopExitMonitor) {
        g_stopExitMonitor = true;
        base::debug::StackTrace stacktrace;
        base::debug::Alias(&stacktrace);
        CrashManager::CrashHandler::instance()->writeMinidump();
    }

    oldExitProcess(uExitCode);
}

BOOL __stdcall myTerminateProcess(HANDLE hProcess, UINT uExitCode)
{
    if (::GetProcessId(hProcess) != ::GetCurrentProcessId()) {
        return oldTerminateProcess(hProcess, uExitCode);
    }

    if (!g_stopExitMonitor) {
        g_stopExitMonitor = true;
        base::debug::StackTrace stacktrace;
        base::debug::Alias(&stacktrace);
        CrashManager::CrashHandler::instance()->writeMinidump();
    }

    return oldTerminateProcess(hProcess, uExitCode);
}

void Logger::startExitMonitor()
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

    atexit(myExit);
    Mhook_SetHook((PVOID*)&oldExitProcess, myExitProcess);
    Mhook_SetHook((PVOID*)&oldTerminateProcess, myTerminateProcess);
}

void Logger::stopExitMonitor()
{
    g_stopExitMonitor = true;
    Mhook_Unhook((PVOID*)&oldExitProcess);
    Mhook_Unhook((PVOID*)&oldTerminateProcess);
}

static QtMessageHandler preMessageHandler = nullptr;

static void myMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
#ifndef _DEBUG
    if (type == QtFatalMsg) {
        g_sm->logger()->info(msg);
        __debugbreak();
    }
#endif
    preMessageHandler(type, context, msg);
}

Logger::Logger(QObject* parent)
    : QObject(parent)
{
}

void Logger::init()
{
    QString logFileName = Profile::logPath();
    mkDir(logFileName);
    log_.setFileName(logFileName);
    log_.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append | QIODevice::Unbuffered);
    this->info(__FUNCTION__);

    preMessageHandler = qInstallMessageHandler(myMessageHandler);
}

void Logger::shutdown()
{
    this->info(__FUNCTION__);
    qInstallMessageHandler(nullptr);
    log_.close();
}

void Logger::info(QString msg)
{
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
