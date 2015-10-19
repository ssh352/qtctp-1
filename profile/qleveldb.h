#ifndef QLEVELDB_H
#define QLEVELDB_H

#include "json_utils.h"

#include <QObject>
#include <QSharedPointer>
#include <QVariant>
#include <QString>
#include <functional>
#include <QMutex>

namespace leveldb {
class DB;
class Status;
}
class QLevelDBBatch;

class QLevelDB : public QObject {
    Q_OBJECT
public:
    enum Status {
        Undefined = -1,
        Ok = 0,
        NotFound = 1,
        Corruption = 2,
        NotSupported = 3,
        InvalidArgument = 4,
        IOError = 5
    };
    explicit QLevelDB(QObject* parent = 0);
    explicit QLevelDB(QString filename, QObject* parent = 0);
    ~QLevelDB();

    QString filename();
    bool opened();
    Status status();
    QString lastError();
    Status open();
    void close();
    bool readStream(std::function<bool(QString, QVariant)> callback, const QString startKey = QString(), const int length = -1);
    void setFilename(QString filename);
    QLevelDBBatch* batch();
    bool del(QString key);
    QVariant get(QString key, QVariant defaultValue = QVariant());
    bool put(QString key, QVariant value);
    bool putSync(QString key, QVariant value);
    bool destroyDB(QString filename);
    bool repairDB(QString filename);

    QWeakPointer<leveldb::DB> dbNativeHandle();

signals:
    void keyValueChanged(QString key, QVariant value);

private slots:
    void onBatchWritten(QSet<QString> keys);

protected:
    QSharedPointer<leveldb::DB> m_levelDB;

private:
    void setStatus(Status status);
    void setLastError(QString text);
    void setOpened(bool opened);
    Status parseStatusCode(leveldb::Status& status);
    void dispatchPropertyChange(QString key, QVariant value);

private:
    Q_DISABLE_COPY(QLevelDB)
    QString m_filename;
    QLevelDBBatch* m_batch;
    bool m_opened;
    Status m_status;
    QString m_lastError;
    QMutex m_mutex;
};

#endif // QLEVELDB_H
