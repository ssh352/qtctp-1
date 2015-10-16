#include "mdsm.h"
#include <QDir>
#include "MdApi.h"
#include "utils.h"
#include "ctpcmd.h"
#include <QMap>
#include <atomic>

//每个合约在内存中使用ringbuffer保留(256)个tick，ui上要延迟1分钟使用请自己复制=
class MdRingBuffer {
public:
    void init(int item_len, int item_count)
    {
        int buflen = item_len * item_count;
        if (buflen > 4 * 1024 * 1024) {
            qFatal("ringbuffer > 4M");
            return;
        }
        buffer_ = new char[item_len * item_count];
        items_ = new void* [item_count];
        for (int i = 0; i < item_count; i++) {
            items_[i] = 0;
        }
        head_ = -1;
        item_count_ = item_count;
        item_len_ = item_len;
    }

    void free()
    {
        delete[] buffer_;
        delete[] items_;
    }

    //需要判断返回值哦=
    void* get(int index)
    {
        if (index < 0)
            return nullptr;

        return items_[index % item_count_];
    }

    int head()
    {
        //原子操作=
        return head_;
    }

    void* put(void* item, int& index)
    {
        index = head_ + 1;
        index = index % item_count_;

        char* buf = buffer_ + index * item_len_;
        items_[index] = buf;
        memcpy(buf, item, item_len_);
        //原子操作=
        head_ = index;

        return buf;
    }

private:
    int item_count_;
    int item_len_;
    void** items_;
    char* buffer_;
    std::atomic_int32_t head_;
};

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
        int index = -1;
        void* item = sm()->saveRb(pDepthMarketData, index);
        emit sm()->gotMdItem(item, index);
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
    , mdspi_(new MdSmSpi(this))
{
}

MdSm::~MdSm()
{
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
    emit this->info("MdSm::start");
    if (mdapi_ != nullptr) {
        qFatal("mdapi_!=nullptr");
        return;
    }

    QDir dir;
    dir.mkpath(flowPath_);
    mdapi_ = MdApi::CreateMdApi(flowPath_.toStdString().c_str());
    CtpCmdMgr::instance()->setMdApi(mdapi_);
    QObject::connect(this, &MdSm::runCmd, CtpCmdMgr::instance(), &CtpCmdMgr::onRunCmd, Qt::QueuedConnection);
    mdapi_->RegisterSpi(mdspi_);
    mdapi_->RegisterFront((char*)qPrintable(front_));
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

void MdSm::initRb(QStringList ids){
    for(int i=0;i<ids.count();i++){
        QString id = ids.at(i);
        MdRingBuffer* rb = new MdRingBuffer;
        rb->init(sizeof(DepthMarketDataField), ringbuffer_len);
        rbs_.insert(id, rb);
    }
}

void MdSm::freeRb()
{
    auto rb_list = rbs_.values();
    for (int i = 0; i < rb_list.length(); i++) {
        MdRingBuffer* rb = rb_list.at(i);
        rb->free();
        delete rb;
    }
    rbs_.clear();
}

void* MdSm::saveRb(void* mdItem, int& index)
{
    DepthMarketDataField* mdf = (DepthMarketDataField*)mdItem;
    QString id = mdf->InstrumentID;
    MdRingBuffer* rb = rbs_.value(id);
    if (rb == nullptr) {
        //预先分配避免多线程锁的问题,这里就不考虑这种情况了=
        //rb = new MdRingBuffer;
        //rb->init(sizeof(DepthMarketDataField), ringbuffer_len);
        //rbs_.insert(id, rb);
        qFatal("rb == nullptr");
    }

    return rb->put(mdItem, index);
}

void* MdSm::getMdItem(QString id, int index)
{
    MdRingBuffer* rb = rbs_.value(id);
    if (!rb) {
        return nullptr;
    }

    return rb->get(index);
}

int MdSm::getMdItemHead(QString id){
    MdRingBuffer* rb = rbs_.value(id);
    if (!rb) {
        return -1;
    }

    return rb->head();
}
