#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"
#include "logindialog.h"

#include "utils.h"
#include <QDir>
#include "mdsm.h"
#include <QThread>
#include "qleveldb.h"
#include "tdsm.h"
#include "ctpcmd.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cmdmgr_(new CtpCmdMgr(this))
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 1);
    cmdmgr_->setInterval(100);
    QObject::connect(cmdmgr_, &CtpCmdMgr::onInfo, this, &MainWindow::onInfo, Qt::QueuedConnection);
    cmdmgr_->start();
}

MainWindow::~MainWindow()
{
    cmdmgr_->stop();
    delete cmdmgr_;
    delete ui;
}

void MainWindow::onMdSmStateChanged(int state)
{
    if (state == MDSM_STOPPED) {
        mdsm_thread_->quit();
        mdsm_thread_ = nullptr;
        mdsm_ = nullptr;
    }

    if (state == MDSM_CONNECTED) {
    }

    if (state == MDSM_DISCONNECTED) {
    }

    if (state == MDSM_LOGINED) {
        //开始用tdapi查询合约列表=
        if (tdsm_ != nullptr) {
            qFatal("tdsm_ != nullptr");
            return;
        }
        tdsm_ = new TdSm;
        tdsm_thread_ = new QThread;
        tdsm_->moveToThread(tdsm_thread_);

        //居然要传一个/结尾
        tdsm_->init(userName_, password_, brokerId_, frontTd_, QDir::temp().absoluteFilePath("hdsrv/tdapi/"), subscribleIds_);
        QObject::connect(tdsm_thread_, &QThread::started, tdsm_, &TdSm::start, Qt::QueuedConnection);
        QObject::connect(tdsm_thread_, &QThread::finished, tdsm_, &TdSm::deleteLater, Qt::QueuedConnection);
        QObject::connect(tdsm_thread_, &QThread::finished, tdsm_thread_, &QThread::deleteLater, Qt::QueuedConnection);
        QObject::connect(tdsm_, &TdSm::onStatusChanged, this, &MainWindow::onTdSmStateChanged, Qt::QueuedConnection);
        QObject::connect(tdsm_, &TdSm::onInfo, this, &MainWindow::onInfo, Qt::QueuedConnection);
        QObject::connect(tdsm_, &TdSm::onGotIds, this, &MainWindow::onGotIds, Qt::QueuedConnection);

        tdsm_thread_->start();
    }
}

void MainWindow::onInfo(QString msg)
{
    ui->listWidget->addItem(msg);
    //滚动到最后一行=
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

void MainWindow::onGotIds(QStringList ids)
{
    //退出td
    tdsm_->logout();

    //设置行=
    ids_row_.clear();
    QStringList sorted_ids = ids;
    sorted_ids.sort();
    this->ui->tableWidget->clearContents();
    this->ui->tableWidget->setRowCount(sorted_ids.length());
    for (int i = 0; i < sorted_ids.length(); i++) {
        QString id = sorted_ids.at(i);
        ids_row_[id] = i;
        QTableWidgetItem* item = new QTableWidgetItem(id);
        ui->tableWidget->setItem(i, 0, item);
    }

    //开始订阅=
    mdsm_->subscrible(ids);
}

void MainWindow::onTdSmStateChanged(int state)
{
    if (state == TDSM_STOPPED) {
        tdsm_thread_->quit();
        tdsm_thread_ = nullptr;
        tdsm_ = nullptr;
    }

    if (state == TDSM_LOGINED) {
    }

    if (state == TDSM_CONNECTED) {
    }

    if (state == TDSM_DISCONNECTED) {
    }

    if (state == TDSM_LOGOUTED) {
        tdsm_->stop();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    onInfo(QString("mdapi version: ") + MdSm::version());
    onInfo(QString("tdapi version: ") + TdSm::version());
}

void MainWindow::on_actionConfig_triggered()
{
    ConfigDialog dlg(this);
    dlg.Load();
    if (dlg.exec()) {
        dlg.Save();
    }
}

void MainWindow::on_actionStart_triggered()
{
    LoginDialog dlg;
    if (dlg.exec()) {
        password_ = dlg.getPassword();
    }
    else {
        return;
    }
    loadCfg();
    if (userName_.length() == 0 || password_.length() == 0 || brokerId_.length() == 0
        || frontMd_.length() == 0 || frontTd_.length() == 0) {
        onInfo("参数无效，请核对参数=");
        return;
    }

    if (mdsm_ != nullptr) {
        qFatal("mdsm_!= nullptr");
    }

    mdsm_ = new MdSm;
    mdsm_thread_ = new QThread;
    mdsm_->moveToThread(mdsm_thread_);

    //居然要传一个/结尾
    mdsm_->init(userName_, password_, brokerId_, frontMd_, QDir::temp().absoluteFilePath("hdsrv/mdapi/"));
    QObject::connect(mdsm_thread_, &QThread::started, mdsm_, &MdSm::start, Qt::QueuedConnection);
    QObject::connect(mdsm_thread_, &QThread::finished, mdsm_, &MdSm::deleteLater, Qt::QueuedConnection);
    QObject::connect(mdsm_thread_, &QThread::finished, mdsm_thread_, &QThread::deleteLater, Qt::QueuedConnection);
    QObject::connect(mdsm_, &MdSm::onStatusChanged, this, &MainWindow::onMdSmStateChanged, Qt::QueuedConnection);
    QObject::connect(mdsm_, &MdSm::onInfo, this, &MainWindow::onInfo, Qt::QueuedConnection);
    QObject::connect(mdsm_, &MdSm::onGotMd, this, &MainWindow::onGotMd, Qt::QueuedConnection);
    mdsm_thread_->start();

    //更新ui
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(true);
}

void MainWindow::loadCfg()
{
    QLevelDB db;
    db.setFilename(QDir::home().absoluteFilePath("hdcfg.db"));
    db.open();
    QVariantMap cfg = db.get("cfg").toMap();
    userName_ = cfg.value("userName", "").toString();
    brokerId_ = cfg.value("brokerId", "").toString();
    frontMd_ = cfg.value("frontMd", "").toString();
    frontTd_ = cfg.value("frontTd", "").toString();
    subscribleIds_ = cfg.value("subscribleIds", "if;ih;ic;sr").toString();
    db.close();
}

void MainWindow::on_actionStop_triggered()
{
    if (tdsm_)
        tdsm_->stop();

    if (mdsm_)
        mdsm_->stop();

    //更新ui
    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);
}

void MainWindow::onGotMd(QVariantMap mdItem)
{
    QString id = mdItem.value("InstrumentID").toString();
    int row = ids_row_.value(id);

    QStringList colList = { "InstrumentID", "TradingDay", "UpdateTime", "UpdateMillisec",
        "LastPrice", "Volume","OpenInterest",
        "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1" };
    for (int i = 0; i < colList.count(); i++) {
        QVariant raw_val = mdItem.value(colList.at(i));
        QString str_val = raw_val.toString();
        if (raw_val.type() == QMetaType::Double || raw_val.type()==QMetaType::Float){
            str_val = QString().sprintf("%6.1f",raw_val.toDouble());
        }

        QTableWidgetItem* item = new QTableWidgetItem(str_val);
        ui->tableWidget->setItem(row, i, item);
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    if (mdsm_ || tdsm_) {
        onInfo("请先停止接收数据=");
        event->ignore();
    }else{
        event->accept();
    }
}
