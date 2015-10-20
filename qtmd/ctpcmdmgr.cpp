#include "ctpcmdmgr.h"
#include "servicemgr.h"
#include "logger.h"
#include "ctpcmd.h"

CtpCmdMgr::CtpCmdMgr(QObject* parent)
    : QObject(parent)
{
}

void CtpCmdMgr::init()
{
    setInterval(100);
    start();
}

void CtpCmdMgr::shutdown()
{
    stop();
    if (cmds_.length() != 0) {
        qFatal("cmds_length() != 0");
    }
}

void CtpCmdMgr::runNow()
{
    if (cmds_.length() == 0)
        return;

    CtpCmd* cmd = cmds_.head();
    cmd->runNow();
    if (cmd->result() == -3) {
        cmd->resetId();
        g_sm->logger()->info(QString().sprintf("发包太快，reqId=%d", cmd->reqId()));
        return;
    }
    cmds_.dequeue();
    delete cmd;
    return;
}
