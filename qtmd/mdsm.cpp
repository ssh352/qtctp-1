#include "mdsm.h"
#include <QDir>
#include "MdApi.h"
#include "utils.h"
#include "ctpcmd.h"
#include <QMap>
#include "ringbuffer.h"
#include "servicemgr.h"
#include "ctpcmdmgr.h"
#include "logger.h"
#include "datapump.h"

///////////
class MdSmSpi : public MdSpi {
public:
    explicit MdSmSpi(MdSm* sm)
        : sm_(sm)
    {
    }

private:
    void OnFrontConnected() override
    {
        info("MdSmSpi::OnFrontConnected");
        emit sm()->statusChanged(MDSM_CONNECTED);
        emit sm()->runCmd(new CmdMdLogin(sm()->userId(), sm()->password(), sm()->brokerId()));
    }

    // 如果网络异常，会直接调用OnFrontDisconnected，需要重置状态数据=
    // 网络错误当再次恢复时候，会自动重连重新走OnFrontConnected
    void OnFrontDisconnected(int nReason) override
    {
        resetData();
        info("MdSmSpi::OnFrontDisconnected");
        emit sm()->statusChanged(MDSM_DISCONNECTED);
    }

    void OnHeartBeatWarning(int nTimeLapse) override
    {
        info("MdSmSpi::OnHeartBeatWarning");
    }

    void OnRspUserLogin(RspUserLoginField* pRspUserLogin, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        info("MdSmSpi::OnRspUserLogin");
        if (!isErrorRsp(pRspInfo, nRequestID) && bIsLast) {
            emit sm()->statusChanged(MDSM_LOGINED);
        }
    }

    // logout在tdapi里面是有效的=
    void OnRspUserLogout(UserLogoutField* pUserLogout, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
    }

    void OnRspError(RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        info(QString().sprintf("MdSmSpi::OnRspError,reqId=%d", nRequestID));
    }

    // 订阅成功了也会调用,目前是不管啥都返回订阅成功=
    void OnRspSubMarketData(SpecificInstrumentField* pSpecificInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        if (!isErrorRsp(pRspInfo, nRequestID) && pSpecificInstrument) {
            QString iid = pSpecificInstrument->InstrumentID;
            got_ids_ << iid;
            //info(QString().sprintf("sub:%s ok", iid.toUtf8().constData()));
        }

        if (bIsLast && got_ids_.length()) {
            QString ids;
            for (auto id : got_ids_) {
                ids = ids + id + ";";
            }
            info(QString().sprintf("total sub ids:%d,%s", got_ids_.length(), ids.toUtf8().constData()));
            emit sm()->statusChanged(MDSM_RECVING);
        }
    }

    void OnRspUnSubMarketData(SpecificInstrumentField* pSpecificInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
    }

    void OnRtnDepthMarketData(DepthMarketDataField* pDepthMarketData) override
    {
        g_sm->dataPump()->put(pDepthMarketData);
    }

private:
    bool isErrorRsp(RspInfoField* pRspInfo, int reqId)
    {
        if (pRspInfo && pRspInfo->ErrorID != 0) {
            info(QString().sprintf("<==错误，reqid=%d,errorId=%d，msg=%s",
                reqId,
                pRspInfo->ErrorID,
                gbk2utf16(pRspInfo->ErrorMsg).toUtf8().constData()));
            return true;
        }
        return false;
    }

    MdSm* sm()
    {
        return sm_;
    }

    void resetData()
    {
        got_ids_.clear();
    }

    void info(QString msg){
        g_sm->logger()->info(msg);
    }

private:
    MdSm* sm_;
    QStringList got_ids_;
};

///////////
MdSm::MdSm(QObject* parent)
    : QObject(parent)
{
}

MdSm::~MdSm()
{
}

bool MdSm::init(QString userId, QString password, QString brokerId, QString frontMd, QString flowPathMd)
{
    userId_ = userId;
    password_ = password;
    brokerId_ = brokerId;
    frontMd_ = frontMd;
    flowPathMd_ = flowPathMd;

    //check
    if (userId_.length() == 0 || password_.length() == 0
            || brokerId_.length() == 0 || frontMd_.length() == 0 || flowPathMd_.length() == 0) {
        return false;
    }
    return true;
}

void MdSm::start()
{
    info("MdSm::start");

    if (mdapi_ != nullptr) {
        qFatal("mdapi_!=nullptr");
        return;
    }

    QDir dir;
    dir.mkpath(flowPathMd_);
    mdapi_ = MdApi::CreateMdApi(flowPathMd_.toStdString().c_str());
    g_sm->ctpCmdMgr()->setMdApi(mdapi_);
    QObject::connect(this, &MdSm::runCmd, g_sm->ctpCmdMgr(), &CtpCmdMgr::onRunCmd);
    mdspi_ = new MdSmSpi(this);
    mdapi_->RegisterSpi(mdspi_);
    mdapi_->RegisterFront((char*)qPrintable(frontMd_));
    mdapi_->Init();
    mdapi_->Join();
    g_sm->ctpCmdMgr()->setMdApi(nullptr);
    info("mdapi::join end!!!");
    emit this->statusChanged(MDSM_STOPPED);
    mdapi_ = nullptr;
    delete mdspi_;
    mdspi_ = nullptr;
}

void MdSm::stop()
{
    info("MdSm::stop");

    if (mdapi_ == nullptr) {
        qFatal("mdapi_==nullptr");
        return;
    }

    mdapi_->RegisterSpi(nullptr);
    mdapi_->Release();
}

void MdSm::subscrible(QStringList ids)
{
    info("MdSm::subscrible");
    emit this->runCmd(new CmdMdSubscrible(ids));
}

QString MdSm::version()
{
    return MdApi::GetApiVersion();
}

void MdSm::info(QString msg){
    g_sm->logger()->info(msg);
}
