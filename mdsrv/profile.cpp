#include "profile.h"
#include "qleveldb.h"
#include <QDir>

Profile::Profile(QObject* parent)
    : QObject(parent)
{
}

void Profile::init()
{
    db_ = new QLevelDB;
    db_->setFilename(QDir::home().absoluteFilePath("mdcfg.db"));
    db_->open();
}

void Profile::shutdown()
{
    db_->close();
    delete db_;
    db_ = nullptr;
}

QString Profile::get(QString k, QString defaultValue)
{
    return db_->get(k, defaultValue).toString();
}

void Profile::put(QString k, QString v)
{
    db_->putSync(k, v);
}

//居然要传一个/结尾=
QString Profile::flowPathMd()
{
    return QDir::temp().absoluteFilePath("hdsrv/mdapi/");
}

//居然要传一个/结尾=
QString Profile::flowPathTd()
{
    return QDir::temp().absoluteFilePath("hdsrv/tdapi/");
}
