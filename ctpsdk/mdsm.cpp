#include "mdsm.h"
#include <QDir>
#include "MdApi.h"
#include "utils.h"
#include "ctpcmd.h"

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
        emit sm()->onInfo("MdSmSpi::OnFrontConnected");
        emit sm()->onStatusChanged(MDSM_CONNECTED);
        emit sm()->onRunCmd(new CmdMdLogin(sm()->userId(), sm()->password(), sm()->brokerId()));
    }

    // 如果网络异常，会直接调用OnFrontDisconnected，需要重置状态数据
    // 网络错误当再次恢复时候，会自动重连重新走OnFrontConnected
    void OnFrontDisconnected(int nReason) override
    {
        resetData();
        emit sm()->onInfo("MdSmSpi::OnFrontDisconnected");
        emit sm()->onStatusChanged(MDSM_DISCONNECTED);
    }

    void OnHeartBeatWarning(int nTimeLapse) override
    {
        emit sm()->onInfo("MdSmSpi::OnHeartBeatWarning");
    }

    void OnRspUserLogin(RspUserLoginField* pRspUserLogin, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->onInfo("MdSmSpi::OnRspUserLogin");
        if (!isErrorRsp(pRspInfo, nRequestID) && bIsLast) {
            emit sm()->onStatusChanged(MDSM_LOGINED);
        }
    }

    // logout在tdapi里面是有效的
    void OnRspUserLogout(UserLogoutField* pUserLogout, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
    }

    void OnRspError(RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->onInfo(QString().sprintf("MdSmSpi::OnRspError,reqId=%d", nRequestID));
    }

    // 订阅成功了也会调用,目前是不管啥都返回订阅成功
    void OnRspSubMarketData(SpecificInstrumentField* pSpecificInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        if (!isErrorRsp(pRspInfo, nRequestID) && pSpecificInstrument) {
            QString iid = pSpecificInstrument->InstrumentID;
            got_ids_ << iid;
            emit sm()->onInfo(QString().sprintf("sub:%s ok", iid.toUtf8().data()));
        }

        if (bIsLast && got_ids_.length()) {
            emit sm()->onStatusChanged(MDSM_RECVING);
        }
    }

    void OnRspUnSubMarketData(SpecificInstrumentField* pSpecificInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
    }

    void OnRtnDepthMarketData(DepthMarketDataField* pDepthMarketData) override
    {
        DepthMarketDataField* mdf = pDepthMarketData;

        if(QString(mdf->InstrumentID).toLower()!="sr601")
            return;

        QString data = QString().sprintf("%8s-%8s-%3d %6s %5.2f %7d %5.2f %3d %5.2f %3d",
                              mdf->TradingDay, mdf->UpdateTime, mdf->UpdateMillisec,
                              mdf->InstrumentID, mdf->LastPrice, mdf->Volume,
                              mdf->BidPrice1, mdf->BidVolume1, mdf->AskPrice1, mdf->AskVolume1);

        emit sm()->onInfo(data);
    }


public:
    bool isErrorRsp(RspInfoField* pRspInfo, int reqId)
    {
        if (pRspInfo && pRspInfo->ErrorID != 0) {
            emit sm()->onInfo(QString().sprintf("<==错误，reqid=%d,errorId=%d，msg=%s", reqId, pRspInfo->ErrorID, gbk2utf16(pRspInfo->ErrorMsg).toUtf8().data()));
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

private:
    MdSm* sm_;
    QStringList got_ids_;
};

///////////
MdSm::MdSm(QObject* parent)
    : QObject(parent)
    , mdspi_(new MdSmSpi(this))
{
}

MdSm::~MdSm()
{
    delete mdspi_;
    mdspi_ = nullptr;
}

void MdSm::init(QString name, QString pwd, QString brokerId, QString front, QString flowPath)
{
    name_ = name;
    pwd_ = pwd;
    brokerId_ = brokerId;
    front_ = front;
    flowPath_ = flowPath;
}

void MdSm::start()
{
    emit this->onInfo("MdSm::start");
    if (mdapi_ != nullptr) {
        qFatal("mdapi_!=nullptr");
        return;
    }

    QDir dir;
    dir.mkpath(flowPath_);
    mdapi_ = MdApi::CreateMdApi(flowPath_.toStdString().c_str());
    CtpCmdMgr::instance()->setMdApi(mdapi_);
    QObject::connect(this, &MdSm::onRunCmd, CtpCmdMgr::instance(), &CtpCmdMgr::onRunCmd, Qt::QueuedConnection);
    mdapi_->RegisterSpi(mdspi_);
    mdapi_->RegisterFront((char*)qPrintable(front_));
    mdapi_->Init();
    mdapi_->Join();
    CtpCmdMgr::instance()->setMdApi(nullptr);
    emit this->onInfo("mdapi::join end!!!");
    emit this->onStatusChanged(MDSM_STOPPED);
}

void MdSm::stop()
{
    emit this->onInfo("MdSm::stop");
    if (mdapi_ == nullptr) {
        qFatal("mdapi_==nullptr");
        return;
    }
    mdapi_->RegisterSpi(nullptr);
    mdapi_->Release();
    mdapi_ = nullptr;
}

void MdSm::subscrible(QStringList ids)
{
    emit this->onInfo("MdSm::subscrible");
    emit this->onRunCmd(new CmdMdSubscrible(ids));
}
