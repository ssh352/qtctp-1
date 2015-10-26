#include "ctpcmdmgr.h"
#include "servicemgr.h"
#include "logger.h"
#include "ctpcmd.h"
#include <windows.h>

CtpCmdMgr::CtpCmdMgr(QObject* parent)
    : QObject(parent)
{
}

void CtpCmdMgr::init()
{
    g_sm->logger()->info(__FUNCTION__);
    //100毫秒执行一次
    setInterval(100);
    start();
}

void CtpCmdMgr::shutdown()
{
    g_sm->logger()->info(__FUNCTION__);
    stop();
    if (cmds_.length() != 0) {
        qFatal("cmds_length() != 0");
    }
}

// 串行执行命令=
void CtpCmdMgr::runNow()
{
    if (cmds_.length() == 0)
        return;

    CtpCmd* cmd = cmds_.head();

    // 检查时间是否到了=
    unsigned long curTick = ::GetTickCount();
    if(curTick < cmd->expires()){
        return;
    }

    // 流控了就一秒后重试=
    cmd->runNow();
    if (cmd->result() == -3) {
        cmd->resetId();
        cmd->setExpires(curTick + 1000);
        g_sm->logger()->info(QString().sprintf("发包太快，reqId=%d", cmd->reqId()));
        return;
    }

    // 消费掉这个cmd=
    cmds_.dequeue();
    delete cmd;
    return;
}

void CtpCmdMgr::onRunCmd(void *p, unsigned int delayTick){
    CtpCmd* cmd = (CtpCmd*)p;
    cmd->setExpires(::GetTickCount() + delayTick);
    cmds_.append(cmd);
}

void CtpCmdMgr::onReset(){
    for(auto cmd : cmds_){
        delete cmd;
    }
    cmds_.clear();
}
