#include "TdSm.h"
#include <QDir>
#include "TraderApi.h"
#include "utils.h"
#include "ctpcmd.h"
#include "servicemgr.h"
#include "ctpcmdmgr.h"
#include "logger.h"

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
        info("TdSmSpi::OnFrontConnected");
        emit sm()->statusChanged(TDSM_CONNECTED);
        emit sm()->runCmd(new CmdTdLogin(sm()->userId(), sm()->password(), sm()->brokerId()));
    }

    // 如果网络异常，会直接调用OnFrontDisconnected，需要重置状态数据=
    // 网络错误当再次恢复时候，会自动重连重新走OnFrontConnected
    void OnFrontDisconnected(int nReason) override
    {
        info("TdSmSpi::OnFrontDisconnected");
        emit sm()->statusChanged(TDSM_DISCONNECTED);

        resetData();
    }

    void OnHeartBeatWarning(int nTimeLapse) override
    {
        info("TdSmSpi::OnHeartBeatWarning");
    }

    void OnRspUserLogin(RspUserLoginField* pRspUserLogin, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        info("TdSmSpi::OnRspUserLogin");
        if (bIsLast && !isErrorRsp(pRspInfo, nRequestID)) {
            emit sm()->statusChanged(TDSM_LOGINED);
            emit sm()->runCmd(new CmdTdQueryInstrument());
        }
    }

    void OnRspUserLogout(UserLogoutField* pUserLogout, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        info("TdSmSpi::OnRspUserLogout");
        if (!isErrorRsp(pRspInfo, nRequestID) && bIsLast) {
            emit sm()->statusChanged(TDSM_LOGOUTED);
        }
    }

    void OnRspError(RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        sm()->info(QString().sprintf("TdSmSpi::OnRspError,reqId=%d", nRequestID));
    }

    // 可能有多次回调=
    void OnRspQryInstrument(InstrumentField* pInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        QString id;
        QString prefix;
        if (!idPrefixList_.length()) {
            QString prefixlist = sm()->idPrefixList();
            idPrefixList_ = prefixlist.split(";");
        }
        if (!isErrorRsp(pRspInfo, nRequestID) && pInstrument) {
            id = pInstrument->InstrumentID;
            if (id.length() <= 6) {
                QString low_id = id.toLower();
                for (int i = 0; i < idPrefixList_.length(); i++) {
                    prefix = idPrefixList_.at(i);
                    if (low_id.startsWith(prefix)) {
                        //info(QString().sprintf("got id:%s", low_id.toUtf8().constData()));
                        ids_ << id;
                        break;
                    }
                }
            }
        }

        if (bIsLast && ids_.length()) {
            QString ids;
            for (auto id : ids_) {
                ids = ids + id + ";";
            }
            info(QString().sprintf("total got ids:%d,%s", ids_.length(), ids.toUtf8().constData()));
            emit sm()->gotIds(ids_);
        }
    }

private:
    bool isErrorRsp(RspInfoField* pRspInfo, int reqId)
    {
        if (pRspInfo && pRspInfo->ErrorID != 0) {
            info(QString().sprintf("<==错误，reqid=%d,errorId=%d，msg=%s", reqId, pRspInfo->ErrorID, gbk2utf16(pRspInfo->ErrorMsg).toUtf8().constData()));
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
        idPrefixList_.clear();
    }

    void info(QString msg)
    {
        g_sm->logger()->info(msg);
    }

private:
    TdSm* sm_;
    QStringList ids_;
    QStringList idPrefixList_;
};

///////////
TdSm::TdSm(QObject* parent)
    : QObject(parent)
{
}

TdSm::~TdSm()
{
}

bool TdSm::init(QString userId, QString password, QString brokerId, QString frontTd, QString flowPathTd, QString idPrefixList)
{
    userId_ = userId;
    password_ = password;
    brokerId_ = brokerId;
    frontTd_ = frontTd;
    flowPathTd_ = flowPathTd;
    idPrefixList_ = idPrefixList;

    // check
    if (userId_.length() == 0 || password_.length() == 0
        || brokerId_.length() == 0 || frontTd_.length() == 0 || flowPathTd_.length() == 0
        || idPrefixList_.length() == 0) {
        return false;
    }

    return true;
}

void TdSm::start()
{
    info("TdSm::start");

    if (tdapi_ != nullptr) {
        qFatal("tdapi_!=nullptr");
        return;
    }

    QDir dir;
    dir.mkpath(flowPathTd_);
    tdapi_ = TraderApi::CreateTraderApi(flowPathTd_.toStdString().c_str());
    g_sm->ctpCmdMgr()->setTdApi(tdapi_);
    QObject::connect(this, &TdSm::runCmd, g_sm->ctpCmdMgr(), &CtpCmdMgr::onRunCmd);
    tdspi_ = new TdSmSpi(this);
    tdapi_->RegisterSpi(tdspi_);
    tdapi_->RegisterFront((char*)qPrintable(frontTd_));
    tdapi_->SubscribePublicTopic(TERT_QUICK);
    tdapi_->SubscribePrivateTopic(TERT_QUICK);
    tdapi_->Init();
    tdapi_->Join();
    g_sm->ctpCmdMgr()->setTdApi(nullptr);
    info("tdapi::join end!!!");
    emit this->statusChanged(TDSM_STOPPED);
    tdapi_ = nullptr;
    delete tdspi_;
    tdspi_ = nullptr;
}

void TdSm::logout()
{
    info("TdSm::logout");
    emit this->runCmd(new CmdTdLogout(userId(), brokerId()));
}

void TdSm::stop()
{
    info("TdSm::stop");

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

void TdSm::info(QString msg)
{
    g_sm->logger()->info(msg);
}