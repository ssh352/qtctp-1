#include "ctpmgr.h"
#include "TraderApi.h"
#include "MdApi.h"
#include "mdsm.h"
#include "tdsm.h"
#include "servicemgr.h"
#include "profile.h"
#include "logger.h"
#include <QThread>
#include "datapump.h"

CtpMgr::CtpMgr(QObject* parent)
    : QObject(parent)
{
}

void CtpMgr::init()
{
}

void CtpMgr::shutdown()
{
}

void CtpMgr::onMdSmStateChanged(int state)
{
    if (state == MDSM_STOPPED) {
        //析构ringbuffer
        g_sm->dataPump()->freeRingBuffer();
        mdsm_thread_->quit();
        mdsm_thread_->wait();
        delete mdsm_thread_;
        mdsm_thread_ = nullptr;
        mdsm_ = nullptr;

        emit mdStopped();
    }
    if (state == MDSM_CONNECTED) {
    }
    if (state == MDSM_DISCONNECTED) {
        //析构ringbuffer
        g_sm->dataPump()->freeRingBuffer();

        emit mdDisconnect();
    }
    if (state == MDSM_LOGINED) {
        //开始用tdapi查询合约列表=
        if (tdsm_ != nullptr) {
            qFatal("tdsm_ != nullptr");
            return;
        }

        // init tdsm
        tdsm_ = new TdSm;
        bool res = tdsm_->init(profile()->get("userId").toString(), password_,
            profile()->get("brokerId").toString(), profile()->get("frontTd").toString(),
            Profile::flowPathTd(), profile()->get("idPrefixList").toString());
        if (!res) {
            delete tdsm_;
            tdsm_ = nullptr;
            logger()->info("参数无效，请核对参数=");
            return;
        }

        // go...
        tdsm_thread_ = new QThread;
        tdsm_->moveToThread(tdsm_thread_);
        QObject::connect(tdsm_thread_, &QThread::started, tdsm_, &TdSm::start);
        QObject::connect(tdsm_thread_, &QThread::finished, tdsm_, &TdSm::deleteLater);
        QObject::connect(tdsm_, &TdSm::statusChanged, this, &CtpMgr::onTdSmStateChanged);
        QObject::connect(tdsm_, &TdSm::gotInstruments, this, &CtpMgr::onGotInstruments);

        tdsm_thread_->start();
    }
}

void CtpMgr::onTdSmStateChanged(int state)
{
    if (state == TDSM_STOPPED) {
        tdsm_thread_->quit();
        tdsm_thread_->wait();
        delete tdsm_thread_;
        tdsm_thread_ = nullptr;
        tdsm_ = nullptr;
    }

    if (state == TDSM_LOGINED) {
    }
    if (state == TDSM_CONNECTED) {
    }
    if (state == TDSM_DISCONNECTED) {
    }
    if (state == TDSM_LOGOUTED) {
        tdsm_->stop();
    }
}

bool CtpMgr::start(QString password)
{
    // check
    if (mdsm_ != nullptr) {
        qFatal("mdsm_!= nullptr");
        return false;
    }

    // init mdsm
    password_ = password;
    mdsm_ = new MdSm;
    bool res = mdsm_->init(profile()->get("userId").toString(), password_,
        profile()->get("brokerId").toString(), profile()->get("frontMd").toString(), Profile::flowPathMd());
    if (!res) {
        delete mdsm_;
        mdsm_ = nullptr;
        logger()->info("参数无效，请核对参数=");
        return false;
    }

    // go...
    mdsm_thread_ = new QThread;
    mdsm_->moveToThread(mdsm_thread_);
    QObject::connect(mdsm_thread_, &QThread::started, mdsm_, &MdSm::start);
    QObject::connect(mdsm_thread_, &QThread::finished, mdsm_, &MdSm::deleteLater);
    QObject::connect(mdsm_, &MdSm::statusChanged, this, &CtpMgr::onMdSmStateChanged);
    mdsm_thread_->start();
    return true;
}

void CtpMgr::stop()
{
    if (tdsm_) {
        tdsm_->stop();
    }

    if (mdsm_) {
        mdsm_->stop();
    }
}

void CtpMgr::onGotInstruments(QStringList ids)
{
    //初始化ringbuffer
    g_sm->dataPump()->initRingBuffer(ids);

    //退出td
    tdsm_->logout();

    // 转发=
    emit this->gotInstruments(ids);

    // 开始订阅=
    mdsm_->subscrible(ids);
}

bool CtpMgr::running()
{
    if (tdsm_ || mdsm_) {
        return true;
    }
    return false;
}

Logger* CtpMgr::logger()
{
    return g_sm->logger();
}

Profile* CtpMgr::profile()
{
    return g_sm->profile();
}
