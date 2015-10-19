#ifndef QLEVELDBBATCH_H
#define QLEVELDBBATCH_H

#include <QMutex>
#include <QObject>
#include <QSet>
#include "json_utils.h"
#include "qleveldb.h"

namespace leveldb {
class DB;
class WriteBatch;
}

class QLevelDBBatch : public QObject {
    Q_OBJECT
public:
    explicit QLevelDBBatch(QWeakPointer<leveldb::DB> db, QObject* parent = 0);
    ~QLevelDBBatch();
    QLevelDBBatch* del(QString key);
    QLevelDBBatch* put(QString key, QVariant value);
    QLevelDBBatch* clear();
    bool write();
signals:
    void batchWritten(QSet<QString> keys);

private:
    Q_DISABLE_COPY(QLevelDBBatch)
    QSharedPointer<leveldb::DB> m_levelDB;
    leveldb::WriteBatch* m_writeBatch;
    QSet<QString> m_operations;
    QMutex m_mutex;
};

#endif // QLEVELDBBATCH_H
