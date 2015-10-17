#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QVariant>

class QLevelDB;
class QLevelDBBatch;

class Profile : public QObject {
    Q_OBJECT
public:
    explicit Profile(QObject* parent = 0);
    void init();
    void shutdown();

public:
    QString get(QString k, QString defaultValue = QString());
    void put(QString k, QString v);

    QVariant getv(QString k, QVariant defaultValue = QVariant());
    void putv(QString k, QVariant v);

    void batchBegin();
    void putvBatch(QString k,QVariant v);
    void putBatch(QString k,QString v);
    bool batchCommit();

    QString flowPathMd();
    QString flowPathTd();

signals:
    void keyValueChanged(QString key, QVariant value);

public slots:

private:
    QLevelDB* db_ = nullptr;
    QLevelDBBatch* batch_ = nullptr;
};

#endif // PROFILE_H
