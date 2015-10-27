#include "datapump.h"
#include "ringbuffer.h"
#include "ApiStruct.h"
#include "servicemgr.h"
#include "logger.h"
#include <windows.h>
#include <QLoggingCategory>
#include "ctpmgr.h"
#include <QDir>
#include <leveldb/db.h>
#include "utils.h"
#include "profile.h"
#include "sdk_utils.h"
#include "leveldbbackend.h"

DataPump::DataPump(QObject* parent)
    : QObject(parent)
{
}

void DataPump::init()
{
    g_sm->logger()->info(__FUNCTION__);
    db_backend_ = new LevelDBBackend;
    db_thread_ = new QThread;
    db_backend_->moveToThread(db_thread_);

    QObject::connect(db_thread_, &QThread::started, db_backend_, &LevelDBBackend::init);
    QObject::connect(db_thread_, &QThread::finished, db_backend_, &LevelDBBackend::shutdown);
    QObject::connect(this, &DataPump::gotTick, db_backend_, &LevelDBBackend::putTick);

    db_thread_->start();
}

//guithread的eventloop退了，不会处理dbthread的finish，这里应该等待线程退出，然后清理qthread对象
//对象属于哪个线程就在哪个线程上清理=
//db_backend_自己删除自己=
void DataPump::shutdown()
{
    g_sm->logger()->info(__FUNCTION__);
    db_thread_->quit();
    db_thread_->wait();
    delete db_thread_;
    db_thread_ = nullptr;
}

//在spi线程上直接调用=
void DataPump::putTick(void* tick)
{
    int indexRb = -1;
    RingBuffer* rb = nullptr;

    if (shouldSkipTick(tick)) {
        return;
    }

    void* newTick = this->putTickToRingBuffer(tick, indexRb, rb);
    fixTickMs(newTick, indexRb, rb);

    emit this->gotTick(newTick, indexRb, rb);
}

// todo(sunwangme):IH在9:15:00时候出现了买一卖一价非常庞大应该是没有初始化的问题，需要处理=
bool DataPump::shouldSkipTick(void *tick){
    // 如果时间无效不保存，如有效区间[09:15:00-15:30:00)[21:00:00-23:30:00) [00:00:00-02:30:00)
    // 交给客户端去做更合理，mdsrv只负责收原始数据=
    if (0){
        char* timeTick = ((DepthMarketDataField*)tick)->UpdateTime;
        bool valid = false;

        // 金融期货 IF 中金所=
        if (memcmp(timeTick, "09:15:00", 8) >= 0 && memcmp(timeTick, "15:30:00", 8) < 0) {
            valid = true;
        };

        // 商品期货 SR 郑商所=
        if (memcmp(timeTick, "09:00:00", 8) >= 0 && memcmp(timeTick, "15:00:00", 8) < 0) {
            valid = true;
        };
        if (memcmp(timeTick, "21:00:00", 8) >= 0 && memcmp(timeTick, "23:30:00", 8) < 0) {
            valid = true;
        };

        // 商品期货 AG 上期所=
        if (memcmp(timeTick, "09:00:00", 8) >= 0 && memcmp(timeTick, "15:00:00", 8) < 0) {
            valid = true;
        };
        if (memcmp(timeTick, "21:00:00", 8) >= 0 && memcmp(timeTick, "23:59:59", 8) <= 0) {
            valid = true;
        };
        if (memcmp(timeTick, "00:00:00", 8) >= 0 && memcmp(timeTick, "02:30:00", 8) < 0) {
            valid = true;
        };

        if (!valid) {
            return true;
        }
    }

    // 如果和前一个tick一样就不保存了（时间，最新价，成交量，持仓量，买一卖一价，买一卖一申报量）
    //白糖会在每次开盘时候，先发一个上次的收盘tick但日期是不一样的，晕。如23号早上9:00:00会
    //收到一个22号的23:29:59的tick但日期却是23号=
    if(1){
        DepthMarketDataField* mdf = (DepthMarketDataField*)tick;
        QString id = mdf->InstrumentID;
        RingBuffer* rb = getRingBuffer(id);
        DepthMarketDataField* lastMdf = (DepthMarketDataField*)rb->get(rb->head());
        if (lastMdf &&
                (memcmp(mdf->UpdateTime, lastMdf->UpdateTime, sizeof(mdf->UpdateTime) - 1) == 0) &&
                (mdf->LastPrice == lastMdf->LastPrice) &&
                (mdf->Volume == lastMdf->Volume) &&
                (mdf->OpenInterest == lastMdf->OpenInterest) &&
                (mdf->BidPrice1 == lastMdf->BidPrice1) &&
                (mdf->BidVolume1 == lastMdf->BidVolume1) &&
                (mdf->AskPrice1 == lastMdf->AskPrice1) &&
                (mdf->AskVolume1 == lastMdf->AskVolume1)) {
            return true;
        }
    }

    // 如果成交量 买一卖一价，买一卖一申报量 都为0，丢弃
    // 白糖会在夜盘之前发一个这样的tick
    // 发现ic会推一个买一卖一为DBL_MAX的东西过来=
    if(1){
        DepthMarketDataField* mdf = (DepthMarketDataField*)tick;
        if ( (mdf->Volume == 0) &&
             (!qIsFinite(mdf->BidPrice1) || mdf->BidPrice1 == 0.0 || mdf->BidPrice1 == DBL_MAX) &&
             (mdf->BidVolume1 == 0) &&
             (!qIsFinite(mdf->AskPrice1) || mdf->AskPrice1 == 0.0 || mdf->AskPrice1 == DBL_MAX) &&
             (mdf->AskVolume1 == 0) ){
            return true;
        }
    }

    return false;
}

void DataPump::putInstrument(void* pInstrument)
{
    leveldb::DB* db = getTodayDB();
    this->db_backend_->putInstrument(pInstrument,db,true,false,false);
}

void DataPump::initRingBuffer(QStringList ids)
{
    if (rbs_.count() != 0) {
        qFatal("rbs_.count() != 0");
    }

    for (auto id : ids) {
        RingBuffer* rb = new RingBuffer;
        rb->init(sizeof(DepthMarketDataField), ringBufferLen_);
        rbs_.insert(id, rb);
    }

    loadRingBufferFromBackend(ids);
}

//修补tick的ms还是需要回读一下=
void DataPump::loadRingBufferFromBackend(QStringList ids)
{
    auto db = getTodayDB();
    for (auto id : ids) {
        auto rb = getRingBuffer(id);

        leveldb::ReadOptions options;
        options.fill_cache = false;
        leveldb::Iterator* it = db->NewIterator(options);
        if (!it) {
            qFatal("NewIterator == nullptr");
        }

        //第一个是tick-id+
        //最后一个是tick-id=
        QString key;
        key = QStringLiteral("tick-") + id + QStringLiteral("=");
        it->Seek(leveldb::Slice(key.toStdString()));
        if (it->Valid()) {
            it->Prev();
        }
        int count = 0;
        for (; it->Valid() && count < rb->count(); it->Prev()) {
            //遇到了前后两个结束item
            auto mdf = (DepthMarketDataField*)it->value().data();
            if (mdf->InstrumentID[0] == 0) {
                break;
            }
            count++;
            if (it->value().size() != sizeof(DepthMarketDataField)) {
                qFatal("it->value().size() != sizeof(DepthMarketDataField)");
            }
            rb->load(rb->count() - count, mdf);
        }
        delete it;
    }
}

void DataPump::freeRingBuffer()
{
    auto rb_list = rbs_.values();
    for (int i = 0; i < rb_list.length(); i++) {
        RingBuffer* rb = rb_list.at(i);
        rb->free();
        delete rb;
    }
    rbs_.clear();
}

void* DataPump::putTickToRingBuffer(void* tick, int& index, RingBuffer*& rb)
{
    DepthMarketDataField* mdf = (DepthMarketDataField*)tick;
    QString id = mdf->InstrumentID;
    rb = getRingBuffer(id);
    return rb->put(tick, index);
}

RingBuffer* DataPump::getRingBuffer(QString id)
{
    RingBuffer* rb = rbs_.value(id);
    if (rb == nullptr) {
        qFatal("rb == nullptr");
    }

    return rb;
}

leveldb::DB* DataPump::getTodayDB()
{
    return db_backend_->getTodayDB();
}

leveldb::DB* DataPump::getHistoryDB()
{
    return db_backend_->getHistoryDB();
}

LevelDBBackend* DataPump::getBackend(){
    return this->db_backend_;
}

// 和前一个tick比较，如果time相同，就改ms为前一个的ms+1，不同，ms改为0
void DataPump::fixTickMs(void* tick, int indexRb, RingBuffer* rb)
{
    DepthMarketDataField* preTick = nullptr;
    DepthMarketDataField* curTick = (DepthMarketDataField*)tick;
    int index = indexRb - 1;
    if (index < 0) {
        index = index + rb->count();
    }
    preTick = (DepthMarketDataField*)rb->get(index);
    if (preTick && strcmp(curTick->UpdateTime, preTick->UpdateTime) == 0) {
        curTick->UpdateMillisec = preTick->UpdateMillisec + 1;
    }
    else {
        curTick->UpdateMillisec = 0;
    }
}

//初始化instrument定位=
void DataPump::initInstrumentLocator()
{
    leveldb::DB* db = getTodayDB();
    db_backend_->initInstrumentLocator(db);
}

//初始化tick定位=
void DataPump::initTickLocator(QString id)
{
    leveldb::DB* db = getTodayDB();
    db_backend_->initTickLocator(id,db,true);
}
