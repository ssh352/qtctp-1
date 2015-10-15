#include "ctpcmd.h"
#include "MdApi.h"
#include "TraderApi.h"

CtpCmdMgr* CtpCmdMgr::this_ = nullptr;
CtpCmdMgr::CtpCmdMgr(QObject *parent) : QObject(parent){
    this_ = this;
}

int CtpCmd::g_reqId_ = 1;

void CtpCmdMgr::runNow(){
    if (cmds_.length() == 0)
        return;

    CtpCmd* cmd = cmds_.head();
    cmd->runNow();
    if (cmd->result() == -3){
        cmd->resetId();
        emit onInfo(QString().sprintf("发包太快，reqid=%d",cmd->reqId()));
        return;
    }
    cmds_.dequeue();
    delete cmd;
    return;
}

void CmdMdLogin::run(){
    ReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strncpy(req.BrokerID, brokerId_.toStdString().c_str(),sizeof(req.BrokerID)-1);
    strncpy(req.UserID, userName_.toStdString().c_str(),sizeof(req.UserID)-1);
    strncpy(req.Password, password_.toStdString().c_str(),sizeof(req.Password)-1);
    result_ = mdapi()->ReqUserLogin(&req, reqId_);
    info("CmdMdLogin");
}

void CmdMdSubscrible::run(){
    QList<std::string> std_ids;
    char** cids = new char*[ids_.length()];
    for(int i=0;i<ids_.length();i++){
        std_ids.append(ids_.at(i).toStdString());
        cids[i] = (char*)std_ids.at(i).c_str();
    }
    result_ = mdapi()->SubscribeMarketData(cids,ids_.length());
    delete[] cids;
    info("CmdMdSubscrible");
}

void CmdTdLogin::run(){
    ReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strncpy(req.BrokerID, brokerId_.toStdString().c_str(),sizeof(req.BrokerID)-1);
    strncpy(req.UserID, userName_.toStdString().c_str(),sizeof(req.UserID)-1);
    strncpy(req.Password, password_.toStdString().c_str(),sizeof(req.Password)-1);
    result_ = tdapi()->ReqUserLogin(&req, reqId_);
    info("CmdTdLogin");
}

void CmdTdLogout::run(){
    UserLogoutField req;
    memset(&req, 0, sizeof(req));
    strncpy(req.BrokerID, brokerId_.toStdString().c_str(),sizeof(req.BrokerID)-1);
    strncpy(req.UserID, userName_.toStdString().c_str(),sizeof(req.UserID)-1);
    result_ = tdapi()->ReqUserLogout(&req, reqId_);
    info("CmdTdLogin");
}

void CmdTdQueryInstrument::run(){
    QryInstrumentField req;
    memset(&req, 0, sizeof(req));
    result_ = tdapi()->ReqQryInstrument(&req, reqId_);
    info("CmdTdQueryInstrument");
}
