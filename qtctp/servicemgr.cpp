#include "servicemgr.h"
#include "profile.h"
#include "logger.h"
#include "ctpcmdmgr.h"
#include "ctpmgr.h"
#include "datapump.h"

ServiceMgr* g_sm = nullptr;

ServiceMgr::ServiceMgr(QObject* parent)
    : QObject(parent)
{
    g_sm = this;
}

//注意init的顺序，后面init的可以访问之前的=
void ServiceMgr::init()
{
    // 调用init前，所有的访问都fatal=
    if (init_ == true) {
        qFatal("init_ == true");
        return;
    }
    init_ = true;

    logger_ = new Logger;
    logger_->init();

    profile_ = new Profile;
    profile_->init();

    ctpCmdMgr_ = new CtpCmdMgr;
    ctpCmdMgr_->init();

    ctpMgr_ = new CtpMgr;
    ctpMgr_->init();

    dataPump_ = new DataPump;
    dataPump_->init();

}

//注意shutdown的顺序，先shutdown的可以访问之后的=
void ServiceMgr::shutdown()
{
    // 调用shutdown后，所有的访问都fatal=
    if (shutdown_ == true) {
        qFatal("shutdown_ == true");
        return;
    }

    dataPump_->shutdown();
    delete dataPump_;
    dataPump_ = nullptr;

    ctpMgr_->shutdown();
    delete ctpMgr_;
    ctpMgr_ = nullptr;

    ctpCmdMgr_->shutdown();
    delete ctpCmdMgr_;
    ctpCmdMgr_ = nullptr;

    profile_->shutdown();
    delete profile_;
    profile_ = nullptr;

    logger_->shutdown();
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

DataPump* ServiceMgr::dataPump(){
    check();

    return this->dataPump_;
}
