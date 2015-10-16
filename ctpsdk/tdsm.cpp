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
        emit sm()->info("TdSmSpi::OnFrontConnected");
        emit sm()->statusChanged(TDSM_CONNECTED);
        emit sm()->runCmd(new CmdTdLogin(sm()->userId(), sm()->password(), sm()->brokerId()));
    }

    // 如果网络异常，会直接调用OnFrontDisconnected，需要重置状态数据
    // 网络错误当再次恢复时候，会自动重连重新走OnFrontConnected
    void OnFrontDisconnected(int nReason) override
    {
        emit sm()->info("TdSmSpi::OnFrontDisconnected");
        emit sm()->statusChanged(TDSM_DISCONNECTED);

        resetData();
    }

    void OnHeartBeatWarning(int nTimeLapse) override
    {
        emit sm()->info("TdSmSpi::OnHeartBeatWarning");
    }

    void OnRspUserLogin(RspUserLoginField* pRspUserLogin, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->info("TdSmSpi::OnRspUserLogin");
        if (bIsLast && !isErrorRsp(pRspInfo, nRequestID)) {
            emit sm()->statusChanged(TDSM_LOGINED);
            emit sm()->runCmd(new CmdTdQueryInstrument());
        }
    }

    void OnRspUserLogout(UserLogoutField* pUserLogout, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->info("TdSmSpi::OnRspUserLogout");
        if (!isErrorRsp(pRspInfo, nRequestID) && bIsLast) {
            emit sm()->statusChanged(TDSM_LOGOUTED);
        }
    }

    void OnRspError(RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->info(QString().sprintf("TdSmSpi::OnRspError,reqId=%d", nRequestID));
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
                        emit sm()->info(QString().sprintf("got id:%s", low_iid.toUtf8().constData()));
                        ids_ << iid;
                        break;
                    }
                }
            }
        }

        if (bIsLast) {
            emit sm()->info(QString().sprintf("total got ids:%d", ids_.length()));
            if (ids_.length()) {
                emit sm()->gotIds(ids_);
            }
        }
    }

public:
    bool isErrorRsp(RspInfoField* pRspInfo, int reqId)
    {
        if (pRspInfo && pRspInfo->ErrorID != 0) {
            emit sm()->info(QString().sprintf("<==错误，reqid=%d,errorId=%d，msg=%s", reqId, pRspInfo->ErrorID, gbk2utf16(pRspInfo->ErrorMsg).toUtf8().constData()));
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
    emit this->info("TdSm::start");
    if (tdapi_ != nullptr) {
        qFatal("tdapi_!=nullptr");
        return;
    }

    QDir dir;
    dir.mkpath(flowPath_);
    tdapi_ = TraderApi::CreateTraderApi(flowPath_.toStdString().c_str());
    CtpCmdMgr::instance()->setTdApi(tdapi_);
    QObject::connect(this, &TdSm::runCmd, CtpCmdMgr::instance(), &CtpCmdMgr::onRunCmd, Qt::QueuedConnection);
    tdapi_->RegisterSpi(tdspi_);
    tdapi_->RegisterFront((char*)qPrintable(front_));
    tdapi_->SubscribePublicTopic(TERT_QUICK);
    tdapi_->SubscribePrivateTopic(TERT_QUICK);
    tdapi_->Init();
    tdapi_->Join();
    CtpCmdMgr::instance()->setTdApi(nullptr);
    emit this->info("tdapi::join end!!!");
    emit this->statusChanged(TDSM_STOPPED);
    tdapi_ = nullptr;
    delete tdspi_;
    tdspi_ = nullptr;
}

void TdSm::logout()
{
    emit this->info("TdSm::logout");
    emit this->runCmd(new CmdTdLogout(userId(), brokerId()));
}

void TdSm::stop()
{
    emit this->info("TdSm::stop");
    if (tdapi_ == nullptr) {
        qFatal("tdapi_==nullptr");
        return;
    }
    tdapi_->RegisterSpi(nullptr);
    tdapi_->Release();
}

QString TdSm::version()
{
    return TraderApi::GetApiVersion();
}
