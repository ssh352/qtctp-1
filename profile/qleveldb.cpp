#include "qleveldb.h"
#include "qleveldbbatch.h"
#include <leveldb/db.h>
#include <QtCore>

QLevelDB::QLevelDB(QObject* parent)
    : QObject(parent)
    , m_batch(nullptr)
    , m_opened(false)
    , m_status(Status::Undefined)
{
}

QLevelDB::QLevelDB(QString filename, QObject* parent)
    : QLevelDB(parent)
{
    setFilename(filename);
}

QLevelDB::~QLevelDB()
{
    close();
}

bool QLevelDB::opened()
{
    return m_opened;
}

QLevelDB::Status QLevelDB::status()
{
    return m_status;
}

QString QLevelDB::lastError()
{
    return m_lastError;
}

QString QLevelDB::filename()
{
    return m_filename;
}

void QLevelDB::setFilename(QString filename)
{
    if (m_filename != filename) {
        m_filename = filename;
        if (opened())
            close();
    }
}

QLevelDB::Status QLevelDB::open()
{
    if (opened()) {
        setStatus(IOError);
        setLastError(QStringLiteral("Database already opened"));
        return m_status;
    }
    else {
        //create directories in path
        QFileInfo fileInfo(m_filename);
        if (!fileInfo.dir().exists()) {
            fileInfo.dir().mkpath(fileInfo.dir().absolutePath());
        }
        //else create a DB object
        leveldb::DB* db;
        leveldb::Options options;

        options.create_if_missing = true;
        options.error_if_exists = false;
        options.compression = leveldb::kNoCompression;
        options.paranoid_checks = false;

        leveldb::Status status = leveldb::DB::Open(options,
            m_filename.toStdString(),
            &db);
        if (status.ok()) {
            m_levelDB.reset(db);
        }
        setOpened(status.ok());
        setLastError(QString::fromStdString(status.ToString()));
        Status code = parseStatusCode(status);
        setStatus(code);
    }
    return m_status;
}

void QLevelDB::close()
{
    if(!opened())
        return;

    delete m_batch;
    m_batch = nullptr;

    m_levelDB.clear();

    setStatus(Status::Undefined);
    setOpened(false);
    setLastError(QString());
}

QLevelDBBatch* QLevelDB::batch()
{
    if (m_batch)
        delete m_batch;
    m_batch = new QLevelDBBatch(m_levelDB.toWeakRef(), this);
    QObject::connect(m_batch, &QLevelDBBatch::batchWritten, this, &QLevelDB::onBatchWritten,Qt::QueuedConnection);
    return m_batch;
}

bool QLevelDB::del(QString key)
{
    leveldb::WriteOptions options;
    leveldb::Status status = m_levelDB.data()->Delete(options, leveldb::Slice(key.toStdString()));

    return status.ok();
}

bool QLevelDB::put(QString key, QVariant value)
{
    //avoid inifine loops
    QVariant oldValue = get(key);
    if (oldValue == value)
        return true;
    leveldb::WriteOptions options;
    QString json = variantToJson(value);
    if (m_opened && m_levelDB) {
        leveldb::Status status = m_levelDB->Put(options,
            leveldb::Slice(key.toStdString()),
            leveldb::Slice(json.toStdString()));
        if (status.ok()) {
            dispatchPropertyChange(key, value);
        }
        return status.ok();
    }
    return false;
}

bool QLevelDB::putSync(QString key, QVariant value)
{
    //avoid inifine loops
    QVariant oldValue = get(key);
    if (oldValue == value)
        return true;
    leveldb::WriteOptions options;
    QString json = variantToJson(value);
    options.sync = true;
    if (m_opened && m_levelDB) {
        leveldb::Status status = m_levelDB->Put(options,
            leveldb::Slice(key.toStdString()),
            leveldb::Slice(json.toStdString()));
        if (status.ok()) {
            dispatchPropertyChange(key, value);
        }
        return status.ok();
    }
    return false;
}

QVariant QLevelDB::get(QString key, QVariant defaultValue)
{
    leveldb::ReadOptions options;
    std::string value = "";
    if (m_opened && !m_levelDB.isNull()) {
        leveldb::Status status = m_levelDB.data()->Get(options,
            leveldb::Slice(key.toStdString()),
            &value);
        if (status.ok())
            return jsonToVariant(QString::fromStdString(value));
    }
    return defaultValue;
}

bool QLevelDB::destroyDB(QString filename)
{
    if (m_filename == filename) {
        setFilename(QString());
    }
    leveldb::Options options;
    leveldb::Status status = leveldb::DestroyDB(filename.toStdString(), options);
    setStatus(parseStatusCode(status));
    setLastError(QString::fromStdString(status.ToString()));
    return m_status;
}

bool QLevelDB::repairDB(QString filename)
{
    leveldb::Options options;
    leveldb::Status status = leveldb::RepairDB(filename.toStdString(), options);
    return status.ok();
}

QWeakPointer<leveldb::DB> QLevelDB::dbNativeHandle()
{
    return m_levelDB.toWeakRef();
}

bool QLevelDB::readStream(std::function<bool(QString, QVariant)> callback, const QString startKey, const int length)
{
    if (!opened() || length == 0)
        return false;

    int llength = length;
    leveldb::ReadOptions options;
    leveldb::Iterator* it = m_levelDB.data()->NewIterator(options);

    if (!it)
        return false;

    if (!startKey.isEmpty())
        it->Seek(leveldb::Slice(startKey.toStdString()));
    else
        it->SeekToFirst();

    for (; it->Valid(); it->Next()) {

        QString key = QString::fromStdString(it->key().ToString());
        QVariant value = jsonToVariant(QString::fromStdString(it->value().ToString()));

        llength--;
        bool shouldContinue = callback(key, value);

        if (!shouldContinue || (length != -1 && length <= 0))
            break;
    }

    delete it;
    return true;
}

void QLevelDB::setStatus(QLevelDB::Status status)
{
    if (m_status != status) {
        m_status = status;
    }
}

void QLevelDB::setLastError(QString text)
{
    if (m_lastError != text) {
        m_lastError = text;
    }
}

void QLevelDB::setOpened(bool opened)
{
    if (m_opened != opened) {
        m_opened = opened;
    }
}

void QLevelDB::onBatchWritten(QSet<QString> keys)
{
    for (auto key : keys) {
        dispatchPropertyChange(key, get(key, QVariant()));
    }
}

QLevelDB::Status QLevelDB::parseStatusCode(leveldb::Status& status)
{
    if (status.ok())
        return Status::Ok;
    if (status.IsCorruption())
        return Status::Corruption;
    if (status.IsIOError())
        return Status::IOError;
    if (status.IsNotFound())
        return Status::NotFound;
    return Status::Undefined;
}

void QLevelDB::dispatchPropertyChange(QString key, QVariant value)
{
    emit keyValueChanged(key, value);
}
