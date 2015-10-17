#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QVariant>

class QLevelDB;

class Profile : public QObject {
    Q_OBJECT
public:
    explicit Profile(QObject* parent = 0);
    void init();
    void shutdown();

public:
    QString get(QString k, QString defaultValue = QString());
    void put(QString k, QString v);
    QString flowPathMd();
    QString flowPathTd();
signals:

public slots:

private:
    QLevelDB* db_ = nullptr;
};

#endif // PROFILE_H
