#include "ctpcmd.h"
#include "MdApi.h"
#include "TraderApi.h"
#include "servicemgr.h"
#include "logger.h"
#include "ctpcmdmgr.h"

///////////////////

int CtpCmd::g_reqId_ = 1;

TraderApi* CtpCmd::tdapi(){
    return g_sm->ctpCmdMgr()->tdapi();
}

MdApi* CtpCmd::mdapi(){
    return g_sm->ctpCmdMgr()->mdapi();
}

void CtpCmd::info(QString msg){
    g_sm->logger()->info(msg);
}

///////////////////

void CmdMdLogin::run()
{
    ReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strncpy(req.BrokerID, brokerId_.toStdString().c_str(), sizeof(req.BrokerID) - 1);
    strncpy(req.UserID, userId_.toStdString().c_str(), sizeof(req.UserID) - 1);
    strncpy(req.Password, password_.toStdString().c_str(), sizeof(req.Password) - 1);
    result_ = mdapi()->ReqUserLogin(&req, reqId_);
    info(QString().sprintf("CmdMdLogin,reqId=%d", reqId_));
}

void CmdMdSubscrible::run()
{
    QList<std::string> std_ids;
    char** cids = new char* [ids_.length()];
    for (int i = 0; i < ids_.length(); i++) {
        std_ids.append(ids_.at(i).toStdString());
        cids[i] = (char*)std_ids.at(i).c_str();
    }
    result_ = mdapi()->SubscribeMarketData(cids, ids_.length());
    delete[] cids;
    info("CmdMdSubscrible");
}

void CmdTdLogin::run()
{
    ReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strncpy(req.BrokerID, brokerId_.toStdString().c_str(), sizeof(req.BrokerID) - 1);
    strncpy(req.UserID, userId_.toStdString().c_str(), sizeof(req.UserID) - 1);
    strncpy(req.Password, password_.toStdString().c_str(), sizeof(req.Password) - 1);
    result_ = tdapi()->ReqUserLogin(&req, reqId_);
    info(QString().sprintf("CmdTdLogin,reqId=%d", reqId_));
}

void CmdTdLogout::run()
{
    UserLogoutField req;
    memset(&req, 0, sizeof(req));
    strncpy(req.BrokerID, brokerId_.toStdString().c_str(), sizeof(req.BrokerID) - 1);
    strncpy(req.UserID, userId_.toStdString().c_str(), sizeof(req.UserID) - 1);
    result_ = tdapi()->ReqUserLogout(&req, reqId_);
    info(QString().sprintf("CmdTdLogout,reqId=%d", reqId_));
}

//不需要确认账单就可以查询合约=
void CmdTdQueryInstrument::run()
{
    QryInstrumentField req;
    memset(&req, 0, sizeof(req));
    result_ = tdapi()->ReqQryInstrument(&req, reqId_);
    info(QString().sprintf("CmdTdQueryInstrument,reqId=%d", reqId_));
}
