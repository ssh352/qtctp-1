#include "leveldbbackend.h"
#include <leveldb/db.h>
#include "ApiStruct.h"
#include "sdk_utils.h"
#include "profile.h"
#include "utils.h"

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
    openTodayDB();
    openHistoryDB();

    initInstrumentLocator(history_db_);
    initInstrumentLocator(today_db_);
}

void LevelDBBackend::shutdown()
{
    closeTodayDB();
    closeHistoryDB();

    delete this;
}

void LevelDBBackend::putTick(void* tick, int indexRb, void* rb)
{
    auto mdf = (DepthMarketDataField*)tick;
    QString id = mdf->InstrumentID;
    auto db = getTodayDB();
    QString key = QString().sprintf("tick-%s-%s-%s-%d", mdf->InstrumentID, mdf->ActionDay, mdf->UpdateTime, mdf->UpdateMillisec);
    leveldb::Slice val((const char*)tick, sizeof(DepthMarketDataField));
    leveldb::WriteOptions options;
    db->Put(options, key.toStdString(), val);
}

leveldb::DB* LevelDBBackend::getTodayDB()
{
    if (today_db_ == nullptr) {
        qFatal("today_db_ == nullptr");
    }
    return today_db_;
}

leveldb::DB* LevelDBBackend::getHistoryDB()
{
    if (history_db_ == nullptr) {
        qFatal("history_db_ == nullptr");
    }
    return history_db_;
}

//只需要在下午5点开始对所有数据进行收盘处理=
void LevelDBBackend::merge(){
    emit mergeBegined();

    QStringList ids = mergeTodayInstruments();
    int progress = 0;
    int step = 100/ids.size();
    for( auto id : ids){
        mergeById(id);
        progress ++ ;
        emit mergeUpdated((progress*step)%100);
    }

    emit mergeEnded();
}

void LevelDBBackend::mergeById(QString id){
    leveldb::DB* db = getTodayDB();
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    QString key;
    key = QStringLiteral("tick-") + id + QStringLiteral("+");
    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }

    BarItem m1;
    TimeType lasttime;
    DateType lastday;
    std::string cid = id.toStdString();
    if (it->Valid()){
        auto mdf = (DepthMarketDataField*)it->value().data();

        memcpy(lastday,mdf->ActionDay,sizeof(DateType));
        memcpy(lasttime,mdf->UpdateTime,sizeof(TimeType));
        memcpy(&lasttime[5],":00",3);
        memset(&m1,0,sizeof(BarItem));
        m1.OpenPrice=m1.ClosePrice=m1.HighestPrice=m1.LowestPrice=mdf->LastPrice;
        m1.OpenInterest=mdf->OpenInterest;
        m1.Volume=mdf->Volume;
    }
    for (; it->Valid(); it->Next()) {
        //遇到了前后两个结束item
        auto mdf = (DepthMarketDataField*)it->value().data();
        if (mdf->InstrumentID[0] == 0) {
            putBarM1(cid.c_str(),lastday,lasttime,&m1);
            break;
        }
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        if (memcmp(lasttime,mdf->UpdateTime,5) != 0){
            putBarM1(cid.c_str(),lastday,lasttime,&m1);

            memcpy(lastday,mdf->ActionDay,sizeof(DateType));
            memcpy(lasttime,mdf->UpdateTime,sizeof(TimeType));
            memcpy(&lasttime[5],":00",3);
            memset(&m1,0,sizeof(BarItem));
            m1.OpenPrice=m1.ClosePrice=m1.HighestPrice=m1.LowestPrice=mdf->LastPrice;
            m1.OpenInterest=mdf->OpenInterest;
            m1.Volume=mdf->Volume;
        }
        //todo(sunwangme):可能会出现不连续的bar，一分钟内无tick就是这样了=
        buildBarM1(&m1,mdf);
    }
    delete it;
}

void LevelDBBackend::buildBarM1(void *bar, void *tick){
    auto mdf = (DepthMarketDataField*)tick;
    auto barItem = (BarItem*)bar;

    if(barItem->HighestPrice < mdf->LastPrice){
        barItem->HighestPrice = mdf->LastPrice;
    }
    if(barItem->LowestPrice > mdf->LastPrice){
        barItem->LowestPrice = mdf->LastPrice;
    }
    barItem->ClosePrice = mdf->LastPrice;

    barItem->Volume = mdf->Volume;
    barItem->OpenInterest = mdf->OpenInterest;
}

void LevelDBBackend::putBarM1(const char* id,char *actionday, char *updatetime, void *bar){
    leveldb::DB* db = getHistoryDB();
    BarItem* barItem = (BarItem*)bar;
    leveldb::Slice val((const char*)barItem, sizeof(BarItem));
    leveldb::WriteOptions options;
    QString key = QString().sprintf("bar-m1-%s-%s-%s", id,actionday,updatetime);
    db->Put(options, key.toStdString(), val);
}

void LevelDBBackend::openHistoryDB(){
    QString path = Profile::historyDbPath();
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
    if (!status.ok()) {
        qFatal("leveldb::DB::Open fail");
    }

    history_db_ = db;
}

void LevelDBBackend::closeHistoryDB(){
    delete history_db_;
}

void LevelDBBackend::openTodayDB(){
    QString path = Profile::todayDbPath();
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
    if (!status.ok()) {
        qFatal("leveldb::DB::Open fail");
    }

    today_db_ = db;
}

void LevelDBBackend::closeTodayDB(){
    delete today_db_;
}

QStringList LevelDBBackend::mergeTodayInstruments(){
    QStringList ids;
    leveldb::DB* db = getTodayDB();
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是instrument+
    //最后一个是instrument=
    QString key;
    key = QStringLiteral("instrument+");
    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }
    for (; it->Valid(); it->Next()) {
        //遇到了前后两个结束item
        auto item = (InstrumentField*)it->value().data();
        if (item->InstrumentID[0] == 0) {
            break;
        }
        if (it->value().size() != sizeof(InstrumentField)) {
            qFatal("it->value().size() != sizeof(InstrumentField)");
        }
        ids << QString(item->InstrumentID);
        putInstrument(item,getHistoryDB(),false,true,false);
    }
    delete it;

    return ids;
}


//初始化instrument定位=
void LevelDBBackend::initInstrumentLocator(leveldb::DB* db)
{
    InstrumentField* idItem = new (InstrumentField);
    memset(idItem, 0, sizeof(InstrumentField));
    QString key;
    leveldb::Slice val((const char*)idItem, sizeof(InstrumentField));
    leveldb::WriteOptions options;
    key = QStringLiteral("instrument+");
    db->Put(options, key.toStdString(), val);
    key = QStringLiteral("instrument=");
    db->Put(options, key.toStdString(), val);

    delete idItem;
}

//初始化tick定位=
void LevelDBBackend::initTickLocator(QString id,leveldb::DB* db,bool raw)
{
    leveldb::Slice val;
    void* buf;

    if(raw){
        DepthMarketDataField* tick = new (DepthMarketDataField);
        memset(tick, 0, sizeof(DepthMarketDataField));
        val = leveldb::Slice((const char*)tick, sizeof(DepthMarketDataField));
        buf = tick;
    }else{
        TickItem* tick = new (TickItem);
        memset(tick, 0, sizeof(TickItem));
        val = leveldb::Slice((const char*)tick, sizeof(TickItem));
        buf = tick;
    }

    QString key;
    leveldb::WriteOptions options;
    key = QStringLiteral("tick-") + id + QStringLiteral("+");
    db->Put(options, key.toStdString(), val);
    key = QStringLiteral("tick-") + id + QStringLiteral("=");
    db->Put(options, key.toStdString(), val);

    delete buf;
}

//初始化bar定位=
void LevelDBBackend::initBarM1Locator(QString id,leveldb::DB* db)
{
    BarItem* bar = new (BarItem);
    memset(bar, 0, sizeof(BarItem));
    QString key;
    leveldb::Slice val((const char*)bar, sizeof(BarItem));
    leveldb::WriteOptions options;
    key = QStringLiteral("bar-m1-") + id + QStringLiteral("+");
    db->Put(options, key.toStdString(), val);
    key = QStringLiteral("bar-m1-") + id + QStringLiteral("=");
    db->Put(options, key.toStdString(), val);

    delete bar;
}

void LevelDBBackend::initBarM5Locator(QString id,leveldb::DB* db)
{
    BarItem* bar = new (BarItem);
    memset(bar, 0, sizeof(BarItem));
    QString key;
    leveldb::Slice val((const char*)bar, sizeof(BarItem));
    leveldb::WriteOptions options;
    key = QStringLiteral("bar-m5-") + id + QStringLiteral("+");
    db->Put(options, key.toStdString(), val);
    key = QStringLiteral("bar-m5-") + id + QStringLiteral("=");
    db->Put(options, key.toStdString(), val);

    delete bar;
}

void LevelDBBackend::putInstrument(void* pInstrument,leveldb::DB* db,bool rawTick,bool barM1,bool barM5)
{
    InstrumentField* instrument = (InstrumentField*)pInstrument;
    QString id = instrument->InstrumentID;

    QString key;
    leveldb::Slice val((const char*)instrument, sizeof(InstrumentField));
    leveldb::WriteOptions options;
    key = QStringLiteral("instrument-") + id;
    db->Put(options, key.toStdString(), val);

    initTickLocator(id,db,rawTick);
    if (barM1){
        initBarM1Locator(id,db);
    }
    if (barM5){
        initBarM5Locator(id,db);
    }
}
