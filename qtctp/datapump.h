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

class DataPump : public QObject {
    Q_OBJECT
public:
    explicit DataPump(QObject* parent = 0);
    void init();
    void shutdown();
    void put(void* mdItem);
    RingBuffer* getRingBuffer(QString id);
    void initRb(QStringList ids);
    void freeRb();

signals:
    void gotMdItem(void* mdItem, int indexRb, void* rb);

public slots:

private:
    void* saveRb(void* mdItem, int& indexRb, RingBuffer*& rb);
    void fixTickMs(void* mdItem, int indexRb, RingBuffer* rb);
    void loadRbFromBackend(QStringList ids);
    void test();

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
    void freeDb();
    void initDb(QStringList ids);
    leveldb::DB* getLevelDB(QString id);

signals:

public slots:
    void onGotMdItem(void* mdItem, int indexRb, void* rb);

private:
    void diagnose(QString foo);

private:
    QMap<QString,leveldb::DB*> dbs_;
};

#endif // DATAPUMP_H
