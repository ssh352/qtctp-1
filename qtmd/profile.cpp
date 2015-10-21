#include "profile.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFIle>
#include "utils.h"

Profile::Profile(QObject* parent)
    : QObject(parent)
{
}

void Profile::init()
{
    path_ = QDir::home().absoluteFilePath("qtmd/config.json");
    mkDir(path_);

    QFile file(path_);
    bool res = file.open(QIODevice::ReadOnly);
    if (!res) {
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isObject()) {
        return;
    }

    QJsonObject obj = doc.object();
    store_ = obj.toVariantMap();
}

void Profile::shutdown()
{
    commit();
}

QVariant Profile::get(QString k, QVariant defaultValue)
{
    return store_.value(k, defaultValue);
}

void Profile::put(QString k, QVariant v)
{
    QVariant old = get(k);
    store_.insert(k, v);
    if (old != v) {
        emit keyValueChanged(k, v);
    }
    dirty_ = true;
}

void Profile::commit()
{
    if (!dirty_) {
        return;
    }

    QJsonObject obj = QJsonObject::fromVariantMap(store_);
    QJsonDocument doc = QJsonDocument(obj);
    QFile file(path_);
    int res = file.open(QIODevice::WriteOnly);
    if (!res) {
        return;
    }
    file.write(doc.toJson(QJsonDocument::Compact));
    file.close();
    dirty_ = false;
}

//居然要传一个/结尾=
QString Profile::flowPathMd()
{
    return QDir::home().absoluteFilePath("qtmd/mdapi/");
}

//居然要传一个/结尾=
QString Profile::flowPathTd()
{
    return QDir::home().absoluteFilePath("qtmd/tdapi/");
}

QString Profile::todayDbPath(){
    return QDir::home().absoluteFilePath("qtmd/data/today");
}

QString Profile::historyDbPath(){
    return QDir::home().absoluteFilePath("qtmd/data/history");
}
