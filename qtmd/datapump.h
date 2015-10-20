#ifndef DATAPUMP_H
#define DATAPUMP_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include <QThread>
#include <QList>

class RingBuffer;
class LevelDBBackend;
namespace leveldb {
class DB;
}

//#define MULTI_DB

class DataPump : public QObject {
    Q_OBJECT
public:
    explicit DataPump(QObject* parent = 0);
    void init();
    void shutdown();
    void put(void* mdItem);
    RingBuffer* getRingBuffer(QString id);
    leveldb::DB* getLevelDB(QString id);
    void initRb(QStringList ids);
    void freeRb();

signals:
    void gotMdItem(void* mdItem, int indexRb, void* rb);
    void initedRb(QStringList ids);
    void freedRb();

public slots:

private:
    void* saveRb(void* mdItem, int& indexRb, RingBuffer*& rb);
    void fixTickMs(void* mdItem, int indexRb, RingBuffer* rb);

private:
    QMap<QString, RingBuffer*> rbs_;
    const int ringBufferLen_ = 256;
    QThread* db_thread_ = nullptr;
    LevelDBBackend* db_backend_ = nullptr;
};

class LevelDBBackend : public QObject{
    Q_OBJECT
public:
    explicit LevelDBBackend(QObject* parent = 0);
    ~LevelDBBackend();
    void init();
    void shutdown();
    leveldb::DB* getLevelDB(QString id);

signals:

public slots:
    void put(void* mdItem, int indexRb, void* rb);
    void freeDb();
    void initDb(QStringList ids);

private:
    void fillRb(QStringList ids);
    void diagnose(QString foo);
    void loadRbFromBackend(QStringList ids);

private:
#ifdef MULTI_DB
    QMap<QString,leveldb::DB*> dbs_;
#else
    leveldb::DB* db_ = nullptr;
#endif
};

#endif // DATAPUMP_H
