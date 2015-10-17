#include "mdsm.h"
#include <QDir>
#include "MdApi.h"
#include "utils.h"
#include "ctpcmd.h"
#include <QMap>
#include "ringbuffer.h"

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
        emit sm()->info("MdSmSpi::OnFrontConnected");
        emit sm()->statusChanged(MDSM_CONNECTED);
        emit sm()->runCmd(new CmdMdLogin(sm()->userId(), sm()->password(), sm()->brokerId()));
    }

    // 如果网络异常，会直接调用OnFrontDisconnected，需要重置状态数据
    // 网络错误当再次恢复时候，会自动重连重新走OnFrontConnected
    void OnFrontDisconnected(int nReason) override
    {
        resetData();
        emit sm()->info("MdSmSpi::OnFrontDisconnected");
        emit sm()->statusChanged(MDSM_DISCONNECTED);
    }

    void OnHeartBeatWarning(int nTimeLapse) override
    {
        emit sm()->info("MdSmSpi::OnHeartBeatWarning");
    }

    void OnRspUserLogin(RspUserLoginField* pRspUserLogin, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->info("MdSmSpi::OnRspUserLogin");
        if (!isErrorRsp(pRspInfo, nRequestID) && bIsLast) {
            emit sm()->statusChanged(MDSM_LOGINED);
        }
    }

    // logout在tdapi里面是有效的
    void OnRspUserLogout(UserLogoutField* pUserLogout, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
    }

    void OnRspError(RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        emit sm()->info(QString().sprintf("MdSmSpi::OnRspError,reqId=%d", nRequestID));
    }

    // 订阅成功了也会调用,目前是不管啥都返回订阅成功
    void OnRspSubMarketData(SpecificInstrumentField* pSpecificInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
        if (!isErrorRsp(pRspInfo, nRequestID) && pSpecificInstrument) {
            QString iid = pSpecificInstrument->InstrumentID;
            got_ids_ << iid;
            emit sm()->info(QString().sprintf("sub:%s ok", iid.toUtf8().constData()));
        }

        if (bIsLast && got_ids_.length()) {
            emit sm()->statusChanged(MDSM_RECVING);
        }
    }

    void OnRspUnSubMarketData(SpecificInstrumentField* pSpecificInstrument, RspInfoField* pRspInfo, int nRequestID, bool bIsLast) override
    {
    }

    void OnRtnDepthMarketData(DepthMarketDataField* pDepthMarketData) override
    {
        int indexRb = -1;
        void* item = sm()->saveRb(pDepthMarketData, indexRb);
        emit sm()->gotMdItem(item, indexRb);
    }

public:
    bool isErrorRsp(RspInfoField* pRspInfo, int reqId)
    {
        if (pRspInfo && pRspInfo->ErrorID != 0) {
            emit sm()->info(QString().sprintf("<==错误，reqid=%d,errorId=%d，msg=%s",
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
    emit this->info("MdSm::start");

    if (mdapi_ != nullptr) {
        qFatal("mdapi_!=nullptr");
        return;
    }

    QDir dir;
    dir.mkpath(flowPathMd_);
    mdapi_ = MdApi::CreateMdApi(flowPathMd_.toStdString().c_str());
    CtpCmdMgr::instance()->setMdApi(mdapi_);
    QObject::connect(this, &MdSm::runCmd, CtpCmdMgr::instance(), &CtpCmdMgr::onRunCmd, Qt::QueuedConnection);
    mdspi_ = new MdSmSpi(this);
    mdapi_->RegisterSpi(mdspi_);
    mdapi_->RegisterFront((char*)qPrintable(frontMd_));
    mdapi_->Init();
    mdapi_->Join();
    CtpCmdMgr::instance()->setMdApi(nullptr);
    emit this->info("mdapi::join end!!!");
    emit this->statusChanged(MDSM_STOPPED);
    mdapi_ = nullptr;
    delete mdspi_;
    mdspi_ = nullptr;
    freeRb();
}

void MdSm::stop()
{
    emit this->info("MdSm::stop");

    if (mdapi_ == nullptr) {
        qFatal("mdapi_==nullptr");
        return;
    }

    mdapi_->RegisterSpi(nullptr);
    mdapi_->Release();
}

void MdSm::subscrible(QStringList ids)
{
    initRb(ids);
    emit this->info("MdSm::subscrible");
    emit this->runCmd(new CmdMdSubscrible(ids));
}

QString MdSm::version()
{
    return MdApi::GetApiVersion();
}

//todo(sunwangme)
//断网自动重连后再次走这里，先free再来=
//这里神马时候释放得想想：disconnect or reconnect？=
void MdSm::initRb(QStringList ids){
    if(rbs_.count()){
        freeRb();
    }

    for(int i=0;i<ids.count();i++){
        QString id = ids.at(i);
        RingBuffer* rb = new RingBuffer;
        rb->init(sizeof(DepthMarketDataField), ringBufferLen_);
        rbs_.insert(id, rb);
    }
}

void MdSm::freeRb()
{
    auto rb_list = rbs_.values();
    for (int i = 0; i < rb_list.length(); i++) {
        RingBuffer* rb = rb_list.at(i);
        rb->free();
        delete rb;
    }
    rbs_.clear();
}

void* MdSm::saveRb(void* mdItem, int& index)
{
    DepthMarketDataField* mdf = (DepthMarketDataField*)mdItem;
    QString id = mdf->InstrumentID;
    RingBuffer* rb = rbs_.value(id);
    if (rb == nullptr) {
        qFatal("rb == nullptr");
    }

    return rb->put(mdItem, index);
}

RingBuffer* MdSm::getRingBuffer(QString id){
    return rbs_.value(id);
}
