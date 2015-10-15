#include "configdialog.h"
#include "ui_configdialog.h"
#include "qleveldb.h"
#include <QDir>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::Save(){
    QLevelDB db;
    db.setFilename(QDir::home().absoluteFilePath("hdcfg.db"));
    db.open();
    QVariantMap cfg;
    cfg.insert("userName",ui->userName->text());
    cfg.insert("brokerId",ui->brokerId->text());
    cfg.insert("frontMd",ui->frontMd->text());
    cfg.insert("frontTd",ui->frontTd->text());
    cfg.insert("subscribleIds",ui->subscribleIds->text());
    db.putSync("cfg",cfg);
    db.close();
}

void ConfigDialog::Load(){
    QLevelDB db;
    db.setFilename(QDir::home().absoluteFilePath("hdcfg.db"));
    db.open();
    QVariantMap cfg = db.get("cfg").toMap();
    ui->userName->setText(cfg.value("userName","").toString());
    ui->brokerId->setText(cfg.value("brokerId","").toString());
    ui->frontMd->setText(cfg.value("frontMd","").toString());
    ui->frontTd->setText(cfg.value("frontTd","").toString());
    ui->subscribleIds->setText(cfg.value("subscribleIds","if;ih;ic;sr").toString());
    db.close();
}
