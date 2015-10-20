#include "historyform.h"
#include "ui_historyform.h"
#include "dbform.h"
#include "servicemgr.h"
#include "datapump.h"
#include "ApiStruct.h"
#include <leveldb/db.h>
#include "utils.h"

HistoryForm::HistoryForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HistoryForm)
{
    ui->setupUi(this);

    //设置列=
    ids_col_ = { "InstrumentID", "ExchangeID", "InstrumentName", "ExchangeInstID",
        "PriceTick", "CreateDate", "OpenDate",
        "ExpireDate", "StartDelivDate" };
    this->ui->tableWidget->setColumnCount(ids_col_.length());
    for (int i = 0; i < ids_col_.length(); i++) {
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(ids_col_.at(i)));
    }
}

HistoryForm::~HistoryForm()
{
    delete ui;
}

void HistoryForm::init()
{

    this->setWindowTitle(QStringLiteral("history"));
    refresh();
}

void HistoryForm::on_refreshButton_clicked()
{
    refresh();
}

void HistoryForm::refresh()
{
    leveldb::DB* db = g_sm->dataPump()->getLevelDB();
    if (!db) {
        return;
    }

    leveldb::ReadOptions options;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        return;
    }

    //第一个是id+
    //最后一个是id=
    QString key;
    key = QStringLiteral("id+");

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }
    for (; it->Valid(); it->Next()) {
        if (it->value().size() != sizeof(InstrumentField)) {
            qFatal("it->value().size() != sizeof(InstrumentField)");
        }
        auto item = (InstrumentField*)it->value().data();
        //遇到了前后两个结束item
        if (item->InstrumentID[0] == 0) {
            break;
        }
        onGotItem(item);
    }
    delete it;
}

void HistoryForm::onGotItem(void* p)
{
    auto item = (InstrumentField*)p;

    QVariantMap mdItem;
    mdItem.insert("InstrumentID", item->InstrumentID);
    mdItem.insert("ExchangeID", item->ExchangeID);
    mdItem.insert("InstrumentName", gbk2utf16(item->InstrumentName));
    mdItem.insert("ExchangeInstID", item->ExchangeInstID);
    mdItem.insert("PriceTick", item->PriceTick);
    mdItem.insert("CreateDate", item->CreateDate);
    mdItem.insert("OpenDate", item->OpenDate);
    mdItem.insert("ExpireDate", item->ExpireDate);
    mdItem.insert("StartDelivDate", item->StartDelivDate);

    //根据id找到对应的行，然后用列的text来在map里面取值设置到item里面=
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    for (int i = 0; i < ids_col_.count(); i++) {
        QVariant raw_val = mdItem.value(ids_col_.at(i));
        QString str_val = raw_val.toString();
        if (raw_val.type() == QMetaType::Double || raw_val.type() == QMetaType::Float) {
            str_val = QString().sprintf("%6.1f", raw_val.toDouble());
        }

        QTableWidgetItem* item = new QTableWidgetItem(str_val);
        ui->tableWidget->setItem(row, i, item);
    }
}

void HistoryForm::on_tableWidget_cellDoubleClicked(int row, int column)
{
    DbForm* form = new DbForm();
    form->setWindowFlags(Qt::Window);
    form->Init(ui->tableWidget->item(row, 0)->text());
    form->show();
}
