#include "qleveldbbatch.h"
#include "json_utils.h"

#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <leveldb/options.h>

QLevelDBBatch::QLevelDBBatch(QWeakPointer<leveldb::DB> db, QObject* parent)
    : QObject(parent)
    , m_levelDB(db)
    , m_writeBatch(new leveldb::WriteBatch())
{
}

QLevelDBBatch::~QLevelDBBatch()
{
    if (m_writeBatch)
        delete m_writeBatch;
}

QLevelDBBatch* QLevelDBBatch::del(QString key)
{
    m_writeBatch->Delete(leveldb::Slice(key.toStdString()));
    return this;
}

QLevelDBBatch* QLevelDBBatch::put(QString key, QVariant value)
{
    QString json = variantToJson(value);
    m_operations.insert(key);

    m_writeBatch->Put(leveldb::Slice(key.toStdString()),
        leveldb::Slice(json.toStdString()));
    return this;
}

QLevelDBBatch* QLevelDBBatch::clear()
{
    m_operations.clear();

    m_writeBatch->Clear();
    return this;
}

bool QLevelDBBatch::write()
{
    leveldb::WriteOptions options;
    options.sync = true;
    if (m_levelDB.isNull())
        return false;
    leveldb::Status status = m_levelDB.data()->Write(options, m_writeBatch);
    if (status.ok()) {
        emit batchWritten(m_operations);
    }
    return status.ok();
}
