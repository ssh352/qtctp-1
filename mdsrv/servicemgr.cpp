#include "servicemgr.h"
#include "profile.h"

ServiceMgr* g_sm = nullptr;

ServiceMgr::ServiceMgr(QObject* parent)
    : QObject(parent)
{
    g_sm = this;
}

void ServiceMgr::init()
{
    profile_ = new Profile;
    profile_->init();
}

void ServiceMgr::shutdown()
{
    if (shutdown_){
        return;
    }

    profile_->shutdown();
    delete profile_;
    profile_ = nullptr;

    shutdown_ = true;
}

bool ServiceMgr::died(){
    return shutdown_;
}

Profile* ServiceMgr::profile()
{
    return this->profile_;
}
