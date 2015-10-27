#include "mergeform.h"
#include "ui_mergeform.h"
#include "servicemgr.h"
#include "datapump.h"
#include "leveldbbackend.h"

MergeForm::MergeForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MergeForm)
{
    ui->setupUi(this);
}

MergeForm::~MergeForm()
{
    delete ui;
}

void MergeForm::init()
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    this->ui->progressBar->setMinimum(0);
    this->ui->progressBar->setMaximum(100);
    this->ui->progressBar->setValue(0);
    this->setWindowTitle(QStringLiteral("Merge"));
}

void MergeForm::on_pushButton_clicked()
{
    QObject::connect(this,&MergeForm::mergeClicked,g_sm->dataPump()->getBackend(),&LevelDBBackend::merge);
    QObject::connect(g_sm->dataPump()->getBackend(),&LevelDBBackend::mergeBegined,this,&MergeForm::beginMerge);
    QObject::connect(g_sm->dataPump()->getBackend(),&LevelDBBackend::mergeUpdated,this,&MergeForm::updateProgress);
    QObject::connect(g_sm->dataPump()->getBackend(),&LevelDBBackend::mergeEnded,this,&MergeForm::endMerge);

    emit mergeClicked();
}

void MergeForm::closeEvent(QCloseEvent* event)
{
    if (merging_) {
        event->ignore();
    }
    else {
        event->accept();
    }
}

void MergeForm::updateProgress(int progress){
    this->ui->progressBar->setValue(progress);
}

void MergeForm::beginMerge(){
    merging_ = true;
    this->ui->pushButton->setEnabled(false);
    this->ui->closeButton->setEnabled(false);
    this->ui->progressBar->setValue(0);
}

void MergeForm::endMerge(){
    merging_ = false;
    this->ui->closeButton->setEnabled(true);
    this->ui->progressBar->setValue(100);
}

void MergeForm::on_closeButton_clicked()
{
    this->close();
}
