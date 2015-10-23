#include "InstrumentsForm.h"
#include "ui_InstrumentsForm.h"
#include "historyform.h"
#include "servicemgr.h"
#include "datapump.h"
#include "ApiStruct.h"
#include <leveldb/db.h>
#include "utils.h"

InstrumentsForm::InstrumentsForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::InstrumentsForm)
{
    ui->setupUi(this);

    //设置列=
    instruments_col_ = { "InstrumentID", "ExchangeID", "InstrumentName", "ExchangeInstID",
        "PriceTick", "CreateDate", "OpenDate",
        "ExpireDate", "StartDelivDate" };
    this->ui->tableWidget->setColumnCount(instruments_col_.length());
    for (int i = 0; i < instruments_col_.length(); i++) {
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(instruments_col_.at(i)));
    }
}

InstrumentsForm::~InstrumentsForm()
{
    delete ui;
}

void InstrumentsForm::init()
{

    this->setWindowTitle(QStringLiteral("instruments"));
    refresh();
}

void InstrumentsForm::on_refreshButton_clicked()
{
    refresh();
}

void InstrumentsForm::refresh()
{
    leveldb::DB* db = g_sm->dataPump()->getLevelDB();
    if (!db) {
        return;
    }

    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        return;
    }

    //第一个是instrument+
    //最后一个是instrument=
    QString key;
    key = QStringLiteral("instrument+");

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
        onGotInstrument(item);
    }
    delete it;
}

void InstrumentsForm::onGotInstrument(void* p)
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

void InstrumentsForm::on_tableWidget_cellDoubleClicked(int row, int column)
{
    HistoryForm* form = new HistoryForm();
    form->setWindowFlags(Qt::Window);
    form->Init(ui->tableWidget->item(row, 0)->text());
    form->show();
}
