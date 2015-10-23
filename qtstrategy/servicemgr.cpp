#include "servicemgr.h"
#include "profile.h"
#include "logger.h"
#include "scriptmgr.h"

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
    scriptMgr_ = new ScriptMgr;

    logger_->init();
    profile_->init();
    scriptMgr_->init();
}

//注意shutdown的顺序，先shutdown的可以访问之后的=
void ServiceMgr::shutdown()
{
    // 调用shutdown后，所有的访问都fatal=
    if (shutdown_ == true) {
        qFatal("shutdown_ == true");
        return;
    }

    scriptMgr_->shutdown();
    profile_->shutdown();
    logger_->shutdown();

    delete scriptMgr_;
    scriptMgr_ = nullptr;

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

ScriptMgr* ServiceMgr::scriptMgr(){
    check();

    return this->scriptMgr_;
}
