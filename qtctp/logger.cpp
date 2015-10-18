#include "logger.h"
#include "CrashHandler.h"

#include <QDir>
#include <QCoreApplication>
#include <crtdbg.h>
#include <windows.h>

Logger::Logger(QObject* parent)
    : QObject(parent)
{
}

void Logger::init()
{
    // Disable the message box for assertions.(see setcrt)
    _CrtSetReportMode(_CRT_ASSERT, 0);

    // Preserve existing error mode, as discussed at http://t/dmea
    UINT new_flags = SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX;
    UINT existing_flags = SetErrorMode(new_flags);
    SetErrorMode(existing_flags | new_flags);

    CrashManager::CrashHandler::instance()->Init(qApp->applicationDirPath(), "c:/windows/system32/notepad.exe");
}

void Logger::shutdown()
{
}
