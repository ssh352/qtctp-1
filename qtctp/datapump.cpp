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
    QObject::connect(this, &DataPump::gotMdItem, db_backend_, &LevelDBBackend::onGotMdItem);

    db_thread_->start();
}

void DataPump::test()
{
    QDir dir = QDir(QDir::home().absoluteFilePath("qtctp/data"));
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    QStringList ids = dir.entryList();
    for (auto id : ids) {
        QString path = QDir::home().absoluteFilePath("qtctp/data/") + id + "/tick";
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

            if (0) {
                DepthMarketDataField* mdItem = new (DepthMarketDataField);
                memset(mdItem, 0, sizeof(DepthMarketDataField));
                QString key;
                leveldb::Slice val((const char*)mdItem, sizeof(DepthMarketDataField));
                leveldb::WriteOptions options;
                key = id + "-tick=";
                db->Put(options, key.toStdString(), val);
                delete mdItem;
            }

            {
                leveldb::ReadOptions options;
                leveldb::Iterator* it = db->NewIterator(options);
                if (!it) {
                    return;
                }
                QString startKey = id + "-tick=";
                it->Seek(leveldb::Slice(startKey.toStdString()));
                int count = 0;
                RingBuffer* rb = new RingBuffer;
                rb->init(sizeof(DepthMarketDataField), 256);
                if (it->Valid()) {
                    it->Prev();
                }
                for (; it->Valid() && count < rb->count(); it->Prev()) {
                    count++;
                    QString key = QString::fromStdString(it->key().ToString());
                    qDebug() << key;
                    if (it->value().size() != sizeof(DepthMarketDataField)) {
                        qFatal("it->value().size() != sizeof(DepthMarketDataField)");
                    }
                    auto mdf = (DepthMarketDataField*)it->value().data();
                    rb->load(rb->count() - count, mdf);
                }
                delete rb;
                delete it;
            }

            delete db;
        }
    }
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

//在ctpmgr线程上一次性完成ringbuffer的初始化操作=
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

    db_backend_->initDb(ids);
    loadRbFromBackend(ids);
}

//在ctpmgr线程上一次性完成ringbuffer的析构操作=
void DataPump::freeRb()
{
    db_backend_->freeDb();

    auto rb_list = rbs_.values();
    for (int i = 0; i < rb_list.length(); i++) {
        RingBuffer* rb = rb_list.at(i);
        rb->free();
        delete rb;
    }
    rbs_.clear();
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

void DataPump::loadRbFromBackend(QStringList ids)
{
    for (auto id : ids) {
        auto rb = getRingBuffer(id);
        auto db = db_backend_->getLevelDB(id);

        leveldb::ReadOptions options;
        leveldb::Iterator* it = db->NewIterator(options);
        if (!it) {
            return;
        }
        //第一个是ID-tick-
        //最后一个是ID-tick=
        QString startKey = id + "-tick=";
        it->Seek(leveldb::Slice(startKey.toStdString()));
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
            rb->load(rb->count() - count, mdf);
        }
        delete it;
    }
}

//////
LevelDBBackend::LevelDBBackend(QObject* parent)
    : QObject(parent)
{
    diagnose(__FUNCTION__);
}

LevelDBBackend::~LevelDBBackend()
{
    diagnose(__FUNCTION__);
}

void LevelDBBackend::diagnose(QString foo)
{
    QString msg = foo + ": " + QString::number(GetCurrentThreadId());
    g_sm->logger()->info(msg);
    qDebug() << msg;
}

void LevelDBBackend::init()
{
    diagnose(__FUNCTION__);
}

void LevelDBBackend::shutdown()
{
    diagnose(__FUNCTION__);

    freeDb();

    delete this;
}

void LevelDBBackend::onGotMdItem(void* mdItem, int indexRb, void* rb)
{
    auto mdf = (DepthMarketDataField*)mdItem;
    QString id = mdf->InstrumentID;
    auto db = dbs_.value(id);
    if (db == nullptr) {
        qFatal("db == nullptr");
    }
    QString key = QString().sprintf("%s-tick-%s-%s-%d", mdf->InstrumentID, mdf->ActionDay, mdf->UpdateTime, mdf->UpdateMillisec);
    leveldb::Slice val((const char*)mdItem, sizeof(DepthMarketDataField));
    leveldb::WriteOptions options;
    db->Put(options, key.toStdString(), val);
}

void LevelDBBackend::initDb(QStringList ids)
{
    if (dbs_.count()) {
        freeDb();
    }

    for (int i = 0; i < ids.count(); i++) {
        QString id = ids.at(i);
        QString path = QDir::home().absoluteFilePath("qtctp/data/") + id + "/tick";
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
            // hack!!!
            if (1) {
                DepthMarketDataField* mdItem = new (DepthMarketDataField);
                memset(mdItem, 0, sizeof(DepthMarketDataField));
                QString key;
                leveldb::Slice val((const char*)mdItem, sizeof(DepthMarketDataField));
                leveldb::WriteOptions options;
                key = id + "-tick=";
                db->Put(options, key.toStdString(), val);
                delete mdItem;
            }
            dbs_.insert(id, db);
        }
    }
}

void LevelDBBackend::freeDb()
{
    auto db_list = dbs_.values();
    for (int i = 0; i < db_list.length(); i++) {
        auto db = db_list.at(i);
        delete db;
    }
    dbs_.clear();
}

leveldb::DB* LevelDBBackend::getLevelDB(QString id)
{
    return dbs_.value(id);
}
