#include "TdSm.h"
#include <QDir>
#include "TraderApi.h"
#include "utils.h"
#include "ctpcmd.h"

///////////
class TdSmSpi : public TraderSpi {
public:
    explicit TdSmSpi(TdSm* sm)
        : sm_(sm)
    {
    }

private:
    void OnFrontConnected() override
    {
        emit sm()->onInfo("TdSmSpi::OnFrontConnected");
        emit sm()->onStatusChanged(TDSM_CONNECTED);
        emit sm()->onRunCmd(new CmdTdLogin(sm()->userId(), sm()->password(), sm()->brokerId()));
    }

    // 如果网络异常，会直接调用OnFrontDisconnected，需要重置状态数据
    // 网络错误当再次恢复时候，会自动重连重新走OnFrontConnected
    void OnFrontDisconnected(int nReason) override
    {
        emit sm()->onInfo("TdSmSpi::OnFrontDisconnected");
        emit sm()->onStatusChanged(TDSM_DISCONNECTED);

        resetData();
    }

    void OnHeartBeatWarning(int nTimeLapse) override
    {
        emit sm()->onInfo("TdSmSpi::OnHeartBeatWarning");
    }

    void OnRspUserLogin(RspUserLoginField* pRspUserLogin, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->onInfo("TdSmSpi::OnRspUserLogin");
        if (bIsLast && !isErrorRsp(pRspInfo, nRequestID)) {
            emit sm()->onStatusChanged(TDSM_LOGINED);
            emit sm()->onRunCmd(new CmdTdQueryInstrument());
        }
    }

    void OnRspUserLogout(UserLogoutField* pUserLogout, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->onInfo("TdSmSpi::OnRspUserLogout");
        if (!isErrorRsp(pRspInfo,nRequestID) && bIsLast){
            emit sm()->onStatusChanged(TDSM_LOGOUTED);
        }
    }

    void OnRspError(RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->onInfo(QString().sprintf("TdSmSpi::OnRspError,reqId=%d", nRequestID));
    }

    // 可能有多次回调
    void OnRspQryInstrument(InstrumentField* pInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        QString iid;
        QString filter;
        if (!idFilters_.length()) {
            QString filters = sm()->idFilters();
            idFilters_ = filters.split(";");
        }
        if (!isErrorRsp(pRspInfo, nRequestID) && pInstrument) {
            iid = pInstrument->InstrumentID;
            if (iid.length() <= 6) {
                QString low_iid = iid.toLower();
                for (int i = 0; i < idFilters_.length(); i++) {
                    filter = idFilters_.at(i);
                    if (low_iid.startsWith(filter)) {
                        emit sm()->onInfo(QString().sprintf("got id:%s", low_iid.toUtf8().data()));
                        ids_ << iid;
                        break;
                    }
                }
            }
        }

        if (bIsLast) {
            emit sm()->onInfo(QString().sprintf("total got ids:%d", ids_.length()));
            if (ids_.length()) {
                emit sm()->onGotIds(ids_);
            }
        }
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

    TdSm* sm()
    {
        return sm_;
    }

    void resetData()
    {
        ids_.clear();
        idFilters_.clear();
    }

private:
    TdSm* sm_;
    QStringList ids_;
    QStringList idFilters_;
};

///////////
TdSm::TdSm(QObject* parent)
    : QObject(parent)
    , tdspi_(new TdSmSpi(this))
{
}

TdSm::~TdSm()
{
    delete tdspi_;
    tdspi_ = nullptr;
}

void TdSm::init(QString name, QString pwd, QString brokerId, QString front, QString flowPath, QString ids)
{
    name_ = name;
    pwd_ = pwd;
    brokerId_ = brokerId;
    front_ = front;
    flowPath_ = flowPath;
    ids_ = ids;
}

void TdSm::start()
{
    emit this->onInfo("TdSm::start");
    if (tdapi_ != nullptr) {
        qFatal("tdapi_!=nullptr");
        return;
    }

    QDir dir;
    dir.mkpath(flowPath_);
    tdapi_ = TraderApi::CreateTraderApi(flowPath_.toStdString().c_str());
    CtpCmdMgr::instance()->setTdApi(tdapi_);
    QObject::connect(this, &TdSm::onRunCmd, CtpCmdMgr::instance(), &CtpCmdMgr::onRunCmd, Qt::QueuedConnection);
    tdapi_->RegisterSpi(tdspi_);
    tdapi_->RegisterFront((char*)qPrintable(front_));
    tdapi_->SubscribePublicTopic(TERT_QUICK);
    tdapi_->SubscribePrivateTopic(TERT_QUICK);
    tdapi_->Init();
    tdapi_->Join();
    CtpCmdMgr::instance()->setTdApi(nullptr);
    emit this->onInfo("tdapi::join end!!!");
    emit this->onStatusChanged(TDSM_STOPPED);
}

void TdSm::logout()
{
    emit this->onInfo("TdSm::logout");
    emit this->onRunCmd(new CmdTdLogout(userId(),brokerId()));
}

void TdSm::stop()
{
    emit this->onInfo("TdSm::stop");
    if (tdapi_ == nullptr) {
        qFatal("tdapi_==nullptr");
        return;
    }
    tdapi_->RegisterSpi(nullptr);
    tdapi_->Release();
    tdapi_ = nullptr;
}
