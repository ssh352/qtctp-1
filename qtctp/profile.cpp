#include "profile.h"
#include "qleveldb.h"
#include "qleveldbbatch.h"

#include <QDir>

Profile::Profile(QObject* parent)
    : QObject(parent)
{
}

void Profile::init()
{
    db_ = new QLevelDB;
    QObject::connect(db_,&QLevelDB::keyValueChanged,this,&Profile::keyValueChanged,Qt::QueuedConnection);
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

QVariant Profile::getv(QString k, QVariant defaultValue)
{
    return db_->get(k, defaultValue);
}

void Profile::putv(QString k, QVariant v)
{
    db_->putSync(k, v);
}

void Profile::batchBegin(){
    batch_ = db_->batch();
}

void Profile::putvBatch(QString k,QVariant v){
    batch_->put(k,v);
}

void Profile::putBatch(QString k,QString v){
    batch_->put(k,v);
}

bool Profile::batchCommit(){
    return batch_->write();
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
