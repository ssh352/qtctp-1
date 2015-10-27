#ifndef LEVELDBBACKEND_H
#define LEVELDBBACKEND_H

#include <QObject>

namespace leveldb {
class DB;
}

class LevelDBBackend : public QObject{
    Q_OBJECT
public:
    explicit LevelDBBackend(QObject* parent = 0);
    ~LevelDBBackend();
    void init();
    void shutdown();
    leveldb::DB* getTodayDB();
    leveldb::DB* getHistoryDB();
    static void initInstrumentLocator(leveldb::DB* db);
    static void initTickLocator(QString id,leveldb::DB* db,bool raw);
    static void initBarM1Locator(QString id,leveldb::DB* db);
    static void initBarM5Locator(QString id,leveldb::DB* db);
    static void putInstrument(void* instrument,leveldb::DB* db,bool rawTick,bool barM1,bool barM5);

signals:
    void mergeBegined();
    void mergeUpdated(int progress);
    void mergeEnded();

public slots:
    void putTick(void* tick, int indexRb, void* rb);
    void merge();

private:
    QStringList mergeTodayInstruments();
    void openHistoryDB();
    void closeHistoryDB();
    void openTodayDB();
    void closeTodayDB();
    void mergeById(QString id);
    void buildBarM1(void* bar,void* tick);
    void putBarM1(const char* id,char* actionday,char* updatetime,void* bar);

private:
    leveldb::DB* today_db_ = nullptr;
    leveldb::DB* history_db_ = nullptr;
};


#endif // LEVELDBBACKEND_H
