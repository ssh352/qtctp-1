#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QVariant>
#include <QMap>

class QLevelDB;
class QLevelDBBatch;

class Profile : public QObject {
    Q_OBJECT
public:
    explicit Profile(QObject* parent = 0);
    void init();
    void shutdown();

public:
    QVariant get(QString k, QVariant defaultValue = QVariant());
    void put(QString k, QVariant v);
    void commit();

    static QString flowPathMd();
    static QString flowPathTd();
    static QString todayDbPath();
    static QString historyDbPath();
    static QString logPath();
    static QString appName();

signals:
    void keyValueChanged(QString key, QVariant value);

public slots:

private:
    QVariantMap store_;
    QString path_;
    bool dirty_ = false;
};

#endif // PROFILE_H
