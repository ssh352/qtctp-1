#include "servicemgr.h"
#include "profile.h"
#include "logger.h"
#include "ctpcmdmgr.h"
#include "ctpmgr.h"
#include "datapump.h"
#include "rpcservice.h"
#include "pushservice.h"

ServiceMgr* g_sm = nullptr;

ServiceMgr::ServiceMgr(QObject* parent)
    : QObject(parent)
{
    g_sm = this;
}

//注意init的顺序，后面init的可以访问之前的=
//注意在init只能调用其他service的object相关的method
//注意目前servicemgr只管理在uithread上的服务，服务可以内建线程=
void ServiceMgr::init()
{
    // 调用init前，所有的访问都fatal=
    if (init_ == true) {
        qFatal("init_ == true");
        return;
    }
    init_ = true;

    logger_ = new Logger;
    profile_ = new Profile;
    ctpCmdMgr_ = new CtpCmdMgr;
    ctpMgr_ = new CtpMgr;
    dataPump_ = new DataPump;
    rpcService_ = new RpcService;
    pushService_ = new PushService;

    logger_->init();
    profile_->init();
    ctpCmdMgr_->init();
    ctpMgr_->init();
    dataPump_->init();
    rpcService_->init();
    pushService_->init();
}

//注意shutdown的顺序，先shutdown的可以访问之后的=
void ServiceMgr::shutdown()
{
    // 调用shutdown后，所有的访问都fatal=
    if (shutdown_ == true) {
        qFatal("shutdown_ == true");
        return;
    }

    pushService_->shutdown();
    rpcService_->shutdown();
    dataPump_->shutdown();
    ctpMgr_->shutdown();
    ctpCmdMgr_->shutdown();
    profile_->shutdown();
    logger_->shutdown();

    delete pushService_;
    pushService_ = nullptr;

    delete rpcService_;
    rpcService_ = nullptr;

    delete dataPump_;
    dataPump_ = nullptr;

    delete ctpMgr_;
    ctpMgr_ = nullptr;

    delete ctpCmdMgr_;
    ctpCmdMgr_ = nullptr;

    delete profile_;
    profile_ = nullptr;

    delete logger_;
    logger_ = nullptr;

    shutdown_ = true;
}

void ServiceMgr::check()
{
    if (shutdown_ || !init_) {
        qFatal("shutdown_ || !init_");
    }
}

Profile* ServiceMgr::profile()
{
    check();

    return this->profile_;
}

Logger* ServiceMgr::logger()
{
    check();

    return this->logger_;
}

CtpCmdMgr* ServiceMgr::ctpCmdMgr()
{
    check();

    return this->ctpCmdMgr_;
}

CtpMgr* ServiceMgr::ctpMgr()
{
    check();

    return this->ctpMgr_;
}

DataPump* ServiceMgr::dataPump()
{
    check();

    return this->dataPump_;
}

RpcService* ServiceMgr::rpcService(){
    check();

    return this->rpcService_;
}

PushService* ServiceMgr::pushService(){
    check();

    return this->pushService_;
}
