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

DataPump::DataPump(QObject* parent)
    : QObject(parent)
{
}

void DataPump::init()
{
    db_backend_ = new LevelDBBackend;
    db_thread_ = new QThread;
    db_backend_->moveToThread(db_thread_);

    QObject::connect(db_thread_, &QThread::started, db_backend_, &LevelDBBackend::init);
    QObject::connect(db_thread_, &QThread::finished, db_backend_, &LevelDBBackend::shutdown);

    QObject::connect(this, &DataPump::gotMdItem, db_backend_, &LevelDBBackend::put);
    QObject::connect(this, &DataPump::freedRb, db_backend_, &LevelDBBackend::freeDb);
    QObject::connect(this, &DataPump::initedRb, db_backend_, &LevelDBBackend::initDb);

    db_thread_->start();
}

//guithread的eventloop退了，不会处理dbthread的finish，这里应该等待线程退出，然后清理qthread对象
//对象属于哪个线程就在哪个线程上清理=
void DataPump::shutdown()
{
    db_thread_->quit();
    db_thread_->wait();
    delete db_thread_;
    db_thread_ = nullptr;
}

//在spi线程上直接调用=
void DataPump::put(void* mdItem)
{
    int indexRb = -1;
    RingBuffer* rb = nullptr;
    void* item = this->saveRb(mdItem, indexRb, rb);
    fixTickMs(item, indexRb, rb);

    emit this->gotMdItem(item, indexRb, rb);
}

void DataPump::initRb(QStringList ids)
{
    if (rbs_.count()) {
        freeRb();
    }

    for (int i = 0; i < ids.count(); i++) {
        QString id = ids.at(i);
        RingBuffer* rb = new RingBuffer;
        rb->init(sizeof(DepthMarketDataField), ringBufferLen_);
        rbs_.insert(id, rb);
    }

    emit initedRb(ids);
}

void DataPump::freeRb()
{
    auto rb_list = rbs_.values();
    for (int i = 0; i < rb_list.length(); i++) {
        RingBuffer* rb = rb_list.at(i);
        rb->free();
        delete rb;
    }
    rbs_.clear();

    emit freedRb();
}

void* DataPump::saveRb(void* mdItem, int& index, RingBuffer*& rb)
{
    DepthMarketDataField* mdf = (DepthMarketDataField*)mdItem;
    QString id = mdf->InstrumentID;
    rb = rbs_.value(id);
    if (rb == nullptr) {
        qFatal("rb == nullptr");
    }

    return rb->put(mdItem, index);
}

RingBuffer* DataPump::getRingBuffer(QString id)
{
    return rbs_.value(id);
}

leveldb::DB* DataPump::getLevelDB(){
    return db_backend_->getLevelDB();
}

// 和前一个tick比较，如果time相同，就改ms为前一个的ms+1，不同，ms改为0
void DataPump::fixTickMs(void* mdItem, int indexRb, RingBuffer* rb)
{
    DepthMarketDataField* preItem = nullptr;
    DepthMarketDataField* curItem = (DepthMarketDataField*)mdItem;
    int index = indexRb - 1;
    if (index < 0) {
        index = index + rb->count();
    }
    preItem = (DepthMarketDataField*)rb->get(index);
    if (preItem && strcmp(curItem->UpdateTime, preItem->UpdateTime) == 0) {
        curItem->UpdateMillisec = preItem->UpdateMillisec + 1;
    }
    else {
        curItem->UpdateMillisec = 0;
    }
}

//////
LevelDBBackend::LevelDBBackend(QObject* parent)
    : QObject(parent)
{
}

LevelDBBackend::~LevelDBBackend()
{
}

void LevelDBBackend::init()
{
    QString path = g_sm->profile()->dbPath() + QStringLiteral("/allinone");
    mkDir(path);
    leveldb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = false;
    options.compression = leveldb::kNoCompression;
    options.paranoid_checks = false;
    leveldb::DB* db;
    leveldb::Status status = leveldb::DB::Open(options,
        path.toStdString(),
        &db);
    if (status.ok()) {

        //初始化id定位=
        {
            InstrumentField* idItem = new (InstrumentField);
            memset(idItem, 0, sizeof(InstrumentField));
            QString key;
            leveldb::Slice val((const char*)idItem, sizeof(InstrumentField));
            leveldb::WriteOptions options;
            key = QStringLiteral("id+");
            db->Put(options, key.toStdString(), val);
            key = QStringLiteral("id=");
            db->Put(options, key.toStdString(), val);
        }

        db_ = db;
    }else{
        qFatal("leveldb::DB::Open fail");
    }
}

void LevelDBBackend::shutdown()
{
    delete db_;
    db_ = nullptr;

    delete this;
}

void LevelDBBackend::put(void* mdItem, int indexRb, void* rb)
{
    auto mdf = (DepthMarketDataField*)mdItem;
    QString id = mdf->InstrumentID;
    auto db = this->getLevelDB();
    if (db == nullptr) {
        qFatal("db == nullptr");
    }
    QString key = QString().sprintf("tick-%s-%s-%s-%d", mdf->InstrumentID, mdf->ActionDay, mdf->UpdateTime, mdf->UpdateMillisec);
    leveldb::Slice val((const char*)mdItem, sizeof(DepthMarketDataField));
    leveldb::WriteOptions options;
    db->Put(options, key.toStdString(), val);
}

void LevelDBBackend::initDb(QStringList ids)
{    
    loadRbFromBackend(ids);
}

void LevelDBBackend::freeDb()
{

}

leveldb::DB* LevelDBBackend::getLevelDB()
{
    return db_;
}

void LevelDBBackend::loadRbFromBackend(QStringList ids)
{
    for (auto id : ids) {
        auto rb = g_sm->dataPump()->getRingBuffer(id);
        auto db = getLevelDB();

        leveldb::ReadOptions options;
        leveldb::Iterator* it = db->NewIterator(options);
        if (!it) {
            return;
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
            count++;
            if (it->value().size() != sizeof(DepthMarketDataField)) {
                qFatal("it->value().size() != sizeof(DepthMarketDataField)");
            }
            auto mdf = (DepthMarketDataField*)it->value().data();
            //遇到了前后两个结束item
            if(mdf->InstrumentID[0]==0){
                break;
            }
            rb->load(rb->count() - count, mdf);
        }
        delete it;
    }

    // 开始订阅=
    g_sm->ctpMgr()->subscrible(ids);
}
