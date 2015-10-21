#include "historyform.h"
#include "ui_HistoryForm.h"
#include "servicemgr.h"
#include "datapump.h"
#include "ApiStruct.h"
#include <leveldb/db.h>

HistoryForm::HistoryForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HistoryForm)
{
    ui->setupUi(this);

    //设置列=
    instruments_col_ = { "InstrumentID", "TradingDay", "UpdateTime", "UpdateMillisec",
        "LastPrice", "Volume", "OpenInterest",
        "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1" };
    this->ui->tableWidget->setColumnCount(instruments_col_.length());
    for (int i = 0; i < instruments_col_.length(); i++) {
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(instruments_col_.at(i)));
    }
}

HistoryForm::~HistoryForm()
{
    delete ui;
}

void HistoryForm::Init(QString id)
{
    id_ = id;
    this->setWindowTitle(QString("history-" + id));

    on_last128_clicked();
}

void HistoryForm::on_first128_clicked()
{
    leveldb::DB* db = g_sm->dataPump()->getLevelDB();
    leveldb::ReadOptions options;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    QString key;
    key = QStringLiteral("tick-") + id_ + QStringLiteral("+");

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }
    int count = 0;
    for (; it->Valid() && count < 128; it->Next()) {
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        auto mdf = (DepthMarketDataField*)it->value().data();
        //遇到了前后两个结束item
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        onGotTick(mdf);
    }
    delete it;
}

void HistoryForm::on_next128_clicked()
{
    if (ui->tableWidget->rowCount() == 0) {
        return;
    }

    leveldb::DB* db = g_sm->dataPump()->getLevelDB();
    leveldb::ReadOptions options;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    int r = ui->tableWidget->rowCount() - 1;
    QString d = ui->tableWidget->item(r, 1)->text();
    QString t = ui->tableWidget->item(r, 2)->text();
    QString m = ui->tableWidget->item(r, 3)->text();
    QString sep = QStringLiteral("-");
    QString key = QStringLiteral("tick-") + id_ + sep + d + sep + t + sep + m;

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }
    int count = 0;
    for (; it->Valid() && count < 128; it->Next()) {
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        auto mdf = (DepthMarketDataField*)it->value().data();
        //遇到了前后两个结束item
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        onGotTick(mdf);
    }
    delete it;
}

void HistoryForm::on_pre128_clicked()
{
    if (ui->tableWidget->rowCount() == 0) {
        return;
    }

    leveldb::DB* db = g_sm->dataPump()->getLevelDB();
    leveldb::ReadOptions options;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    int r = ui->tableWidget->rowCount() - 1;
    QString d = ui->tableWidget->item(r, 1)->text();
    QString t = ui->tableWidget->item(r, 2)->text();
    QString m = ui->tableWidget->item(r, 3)->text();
    QString sep = QStringLiteral("-");
    QString key = QStringLiteral("tick-") + id_ + sep + d + sep + t + sep + m;

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Prev();
    }
    int count = 0;
    for (; it->Valid() && count < 128; it->Prev()) {
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        auto mdf = (DepthMarketDataField*)it->value().data();
        //遇到了前后两个结束item
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        onGotTick(mdf);
    }
    delete it;
}

void HistoryForm::on_last128_clicked()
{
    leveldb::DB* db = g_sm->dataPump()->getLevelDB();
    leveldb::ReadOptions options;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是ID-tick+
    //最后一个是ID-tick=
    QString key = QStringLiteral("tick-") + id_ + QStringLiteral("=");

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Prev();
    }
    int count = 0;
    for (; it->Valid() && count < 128; it->Prev()) {
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        auto mdf = (DepthMarketDataField*)it->value().data();
        //遇到了前后两个结束item
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        onGotTick(mdf);
    }
    delete it;
}

void HistoryForm::onGotTick(void* tick)
{
    auto mdf = (DepthMarketDataField*)tick;

    QVariantMap mdItem;
    mdItem.insert("InstrumentID", mdf->InstrumentID);
    mdItem.insert("TradingDay", mdf->TradingDay);
    mdItem.insert("UpdateTime", mdf->UpdateTime);
    mdItem.insert("UpdateMillisec", mdf->UpdateMillisec);
    mdItem.insert("LastPrice", mdf->LastPrice);
    mdItem.insert("Volume", mdf->Volume);
    mdItem.insert("OpenInterest", mdf->OpenInterest);
    mdItem.insert("BidPrice1", mdf->BidPrice1);
    mdItem.insert("BidVolume1", mdf->BidVolume1);
    mdItem.insert("AskPrice1", mdf->AskPrice1);
    mdItem.insert("AskVolume1", mdf->AskVolume1);

    //根据id找到对应的行，然后用列的text来在map里面取值设置到item里面=
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    for (int i = 0; i < instruments_col_.count(); i++) {
        QVariant raw_val = mdItem.value(instruments_col_.at(i));
        QString str_val = raw_val.toString();
        if (raw_val.type() == QMetaType::Double || raw_val.type() == QMetaType::Float) {
            str_val = QString().sprintf("%6.1f", raw_val.toDouble());
        }

        QTableWidgetItem* item = new QTableWidgetItem(str_val);
        ui->tableWidget->setItem(row, i, item);
    }
}
