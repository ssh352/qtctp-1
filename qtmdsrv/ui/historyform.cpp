#include "historyform.h"
#include "ui_historyform.h"
#include "servicemgr.h"
#include "ApiStruct.h"
#include <leveldb/db.h>
#include "QMessageBox"
#include <QDebug>
#include "sdk_utils.h"

HistoryForm::HistoryForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HistoryForm)
{
    ui->setupUi(this);

    //设置上下分割=
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 1);

    //设置graph
    initGraph();
}

HistoryForm::~HistoryForm()
{
    delete ui;
}

void HistoryForm::init(QString id,leveldb::DB* db,bool display_bar)
{
    id_ = id;
    db_ = db;
    display_bar_ = display_bar;

    //设置列=
    if(display_bar_){
        instruments_col_ = {"Key",
            "OpenPrice","ClosePrice","HighestPrice","LowestPrice",
            "Volume", "OpenInterest"};
        this->ui->tableWidget->setColumnCount(instruments_col_.length());
        for (int i = 0; i < instruments_col_.length(); i++) {
            ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(instruments_col_.at(i)));
        }
    }
    else{
        instruments_col_ = {"Key",
            "LastPrice", "Volume", "OpenInterest",
            "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1" };
        this->ui->tableWidget->setColumnCount(instruments_col_.length());
        for (int i = 0; i < instruments_col_.length(); i++) {
            ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(instruments_col_.at(i)));
        }
    }
    this->ui->tableWidget->setColumnWidth(0,250);

    if(display_bar_){
        this->setWindowTitle(QString("history-bar-" + id));
        on_last128Bar_clicked();
    }else{
        this->setWindowTitle(QString("history-tick-" + id));
        on_last128Tick_clicked();
    }
}

void HistoryForm::on_first128_clicked(){
    if(display_bar_){
        on_first128Bar_clicked();
    }else{
        on_first128Tick_clicked();
    }
}

void HistoryForm::on_next128_clicked(){
    if(display_bar_){
        on_next128Bar_clicked();
    }else{
        on_next128Tick_clicked();
    }
}

void HistoryForm::on_pre128_clicked(){
    if(display_bar_){
        on_pre128Bar_clicked();
    }else{
        on_pre128Tick_clicked();
    }
}

void HistoryForm::on_last128_clicked(){
    if(display_bar_){
        on_last128Bar_clicked();
    }else{
        on_last128Tick_clicked();
    }
}

void HistoryForm::on_seekButton_clicked(){
    if(display_bar_){
        on_seekButtonBar_clicked();
    }else{
        on_seekButtonTick_clicked();
    }
}
void HistoryForm::on_first128Tick_clicked()
{
    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
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
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Next()) {
        //遇到了前后两个结束item
        auto mdf = (DepthMarketDataField*)it->value().data();
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        x_.append(count);
        onGotTick(QString::fromStdString(it->key().ToString()),mdf);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_next128Tick_clicked()
{
    if (ui->tableWidget->rowCount() == 0) {
        return;
    }

    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    int r = ui->tableWidget->rowCount() - 1;
    QString key = ui->tableWidget->item(r, 0)->text();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Next()) {
        //遇到了前后两个结束item
        auto mdf = (DepthMarketDataField*)it->value().data();
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        x_.append(count);
        onGotTick(QString::fromStdString(it->key().ToString()),mdf);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_pre128Tick_clicked()
{
    if (ui->tableWidget->rowCount() == 0) {
        return;
    }

    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    int r = ui->tableWidget->rowCount() - 1;
    QString key = ui->tableWidget->item(r, 0)->text();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Prev();
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Prev()) {
        //遇到了前后两个结束item
        auto mdf = (DepthMarketDataField*)it->value().data();
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        x_.append(count);
        onGotTick(QString::fromStdString(it->key().ToString()),mdf);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_last128Tick_clicked()
{
    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    QString key = QStringLiteral("tick-") + id_ + QStringLiteral("=");

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Prev();
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Prev()) {
        //遇到了前后两个结束item
        auto mdf = (DepthMarketDataField*)it->value().data();
        if (mdf->InstrumentID[0] == 0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            qFatal("it->value().size() != sizeof(DepthMarketDataField)");
        }
        x_.append(count);
        onGotTick(QString::fromStdString(it->key().ToString()),mdf);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_first128Bar_clicked(){
    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是bar-m1-id+
    //最后一个是bar-m1-id=
    QString key;
    key = QStringLiteral("bar-m1-") + id_ + QStringLiteral("+");

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Next()) {
        //遇到了前后两个结束item
        auto barItem = (BarItem*)it->value().data();
        if (barItem->OpenInterest == 0.0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(BarItem)) {
            qFatal("it->value().size() != sizeof(BarItem)");
        }
        x_.append(count);
        onGotBarM1(QString::fromStdString(it->key().ToString()),barItem);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_next128Bar_clicked(){
    if (ui->tableWidget->rowCount() == 0) {
        return;
    }

    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是bar-m1-id+
    //最后一个是bar-m1-id=
    int r = ui->tableWidget->rowCount() - 1;
    QString key = ui->tableWidget->item(r, 0)->text();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Next();
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Next()) {
        //遇到了前后两个结束item
        auto barItem = (BarItem*)it->value().data();
        if (barItem->OpenInterest == 0.0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(BarItem)) {
            qFatal("it->value().size() != sizeof(BarItem)");
        }
        x_.append(count);
        onGotBarM1(QString::fromStdString(it->key().ToString()),barItem);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_pre128Bar_clicked(){
    if (ui->tableWidget->rowCount() == 0) {
        return;
    }

    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是bar-m1-id+
    //最后一个是bar-m1-id=
    int r = ui->tableWidget->rowCount() - 1;
    QString key = ui->tableWidget->item(r, 0)->text();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Prev();
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Prev()) {
        //遇到了前后两个结束item
        auto barItem = (BarItem*)it->value().data();
        if (barItem->OpenInterest == 0.0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(BarItem)) {
            qFatal("it->value().size() != sizeof(BarItem)");
        }
        x_.append(count);
        onGotBarM1(QString::fromStdString(it->key().ToString()),barItem);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_last128Bar_clicked(){
    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是bar-m1-id+
    //最后一个是bar-m1-id=
    QString key = QStringLiteral("bar-m1-") + id_ + QStringLiteral("=");

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    it->Seek(leveldb::Slice(key.toStdString()));
    if (it->Valid()) {
        it->Prev();
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Prev()) {
        //遇到了前后两个结束item
        auto barItem = (BarItem*)it->value().data();
        if (barItem->OpenInterest == 0.0) {
            break;
        }
        count++;
        if (it->value().size() != sizeof(BarItem)) {
            qFatal("it->value().size() != sizeof(BarItem)");
        }
        x_.append(count);
        onGotBarM1(QString::fromStdString(it->key().ToString()),barItem);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_seekButtonTick_clicked(){
    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是tick-id+
    //最后一个是tick-id=
    QString key = ui->lineEdit->text();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QString msg("not found,input format:\ntick-IF1511-\ntick-IF1511-20151023-1304\ntick-IF1511-20151023-13:04:00-0");
    it->Seek(leveldb::Slice(key.toStdString()));
    if(!it->Valid()){
        QMessageBox::warning(this,"seek",msg);
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Prev()) {
        //遇到了前后两个结束item
        auto mdf = (DepthMarketDataField*)it->value().data();
        if (mdf->InstrumentID[0] == 0) {
            if (count ==0) QMessageBox::warning(this,"seek",msg);
            break;
        }
        //遇到了instrument数据=
        if (it->value().size() != sizeof(DepthMarketDataField)) {
            if (count ==0) QMessageBox::warning(this,"seek",msg);
            break;
        }
        count++;
        onGotTick(QString::fromStdString(it->key().ToString()),mdf);
        x_.append(count);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_seekButtonBar_clicked(){
    leveldb::DB* db = db_;
    leveldb::ReadOptions options;
    options.fill_cache = false;
    leveldb::Iterator* it = db->NewIterator(options);
    if (!it) {
        qFatal("NewIterator == nullptr");
    }

    //第一个是bar-m1-id+
    //最后一个是bar-m1-id=
    QString key = ui->lineEdit->text();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QString msg("not found,input format:\nbar-m1-IF1511-\nbar-m1-IF1511-20151023-13:04");
    it->Seek(leveldb::Slice(key.toStdString()));
    if(!it->Valid()){
        QMessageBox::warning(this,"seek",msg);
    }
    int count = 0;
    x_.clear();y_.clear();
    for (; it->Valid() && count < 128; it->Prev()) {
        //遇到了前后两个结束item
        auto barItem = (BarItem*)it->value().data();
        if (barItem->OpenInterest == 0.0) {
            if (count ==0) QMessageBox::warning(this,"seek",msg);
            break;
        }
        //遇到了instrument数据=
        if (it->value().size() != sizeof(BarItem)) {
            if (count ==0) QMessageBox::warning(this,"seek",msg);
            break;
        }
        count++;
        onGotBarM1(QString::fromStdString(it->key().ToString()),barItem);
        x_.append(count);
    }
    delete it;
    drawGraph();
}

void HistoryForm::on_delButton_clicked(){
    leveldb::DB* db = db_;
    QString key = ui->lineEdit->text();
    leveldb::ReadOptions options;
    std::string val;
    leveldb::Status status = db->Get(options,key.toStdString(),&val);
    if (status.ok()){
        leveldb::WriteOptions options;
        status = db->Delete(options,key.toStdString());
    }

    if(status.ok()){
        QMessageBox::about(this,"del","ok");
    }
    else{
       QString errStr = QString::fromStdString(status.ToString());
       QMessageBox::warning(this,"del",errStr);
    }
}

void HistoryForm::onGotTick(QString key,void* tick)
{
    auto mdf = (DepthMarketDataField*)tick;
    y_.append(mdf->LastPrice);

    QVariantMap mdItem;
    mdItem.insert("Key", key);
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

void HistoryForm::onGotBarM1(QString key,void* bar)
{
    auto barItem = (BarItem*)bar;
    y_.append(barItem->ClosePrice);

    QVariantMap mdItem;
    mdItem.insert("Key", key);
    mdItem.insert("OpenPrice", barItem->OpenPrice);
    mdItem.insert("ClosePrice", barItem->ClosePrice);
    mdItem.insert("HighestPrice", barItem->HighestPrice);
    mdItem.insert("LowestPrice", barItem->LowestPrice);
    mdItem.insert("Volume", barItem->Volume);
    mdItem.insert("OpenInterest", barItem->OpenInterest);

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

#ifdef USE_QCUSTOMPLOT
void HistoryForm::initGraph()
{
    ui->tickPlot->addGraph();
}

void HistoryForm::drawGraph(){
    ui->tickPlot->graph()->setData(x_, y_);
    ui->tickPlot->graph()->rescaleAxes(false);
    ui->tickPlot->xAxis->scaleRange(1.1, ui->tickPlot->xAxis->range().center());
    ui->tickPlot->yAxis->scaleRange(1.1, ui->tickPlot->yAxis->range().center());
    ui->tickPlot->xAxis->setTicks(true);
    ui->tickPlot->yAxis->setTicks(true);
    ui->tickPlot->axisRect()->setupFullAxesBox();
    ui->tickPlot->replot();
}
#else
#include "qwt_plot_curve.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_grid.h"
void HistoryForm::initGraph()
{
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setFrameStyle( QFrame::NoFrame );
    canvas->setBorderRadius( 3 );
    ui->tickPlot->setCanvas( canvas );
    ui->tickPlot->setCanvasBackground( Qt::white );

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->setPen( Qt::gray, 0 , Qt::DotLine );
    grid->attach( ui->tickPlot );

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setPen( Qt::blue, 1 ),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve->attach( ui->tickPlot );
    curve_ = curve;
}

void HistoryForm::drawGraph(){
    curve_->setSamples(x_,y_);
    ui->tickPlot->replot();
}
#endif
