#include "configdialog.h"
#include "ui_configdialog.h"
#include "servicemgr.h"
#include "profile.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    setWindowTitle("config");
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::Save(){
    Profile* profile = g_sm->profile();
    profile->batchBegin();
    profile->putBatch("userId",ui->userId->text());
    profile->putBatch("brokerId",ui->brokerId->text());
    profile->putBatch("frontMd",ui->frontMd->text());
    profile->putBatch("frontTd",ui->frontTd->text());
    profile->putBatch("idPrefixList",ui->idPrefixList->text());
    profile->batchCommit();
}

void ConfigDialog::Load(){
    Profile* profile = g_sm->profile();
    ui->userId->setText(profile->get("userId",""));
    ui->brokerId->setText(profile->get("brokerId",""));
    ui->frontMd->setText(profile->get("frontMd",""));
    ui->frontTd->setText(profile->get("frontTd",""));
    ui->idPrefixList->setText(profile->get("idPrefixList","if;ih;ic;sr"));
}
