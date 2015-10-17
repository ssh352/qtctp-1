#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"
#include "logindialog.h"

#include "utils.h"
#include "mdsm.h"
#include <QThread>
#include "tdsm.h"
#include "ctpcmd.h"
#include <QCloseEvent>
#include "ApiStruct.h"
#include "tickform.h"
#include "servicemgr.h"
#include "profile.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cmdmgr_(new CtpCmdMgr(this))
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 1);
    setWindowTitle("mdsrv");

    //设置cmdmgr
    cmdmgr_->setInterval(100);
    QObject::connect(cmdmgr_, &CtpCmdMgr::onInfo, this, &MainWindow::onInfo, Qt::QueuedConnection);
    cmdmgr_->start();

    //设置trayicon
    this->createActions();
    this->createTrayIcon();

    //设置列=
    ids_col_ = { "InstrumentID", "TradingDay", "UpdateTime", "UpdateMillisec",
        "LastPrice", "Volume", "OpenInterest",
        "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1" };
    this->ui->tableWidget->setColumnCount(ids_col_.length());
    for (int i = 0; i < ids_col_.length(); i++) {
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(ids_col_.at(i)));
    }

    // profile
    profile_ = g_sm->profile();
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

        // init tdsm
        tdsm_ = new TdSm;
        bool res = tdsm_->init(profile_->get("userId"), password_,
            profile_->get("brokerId"), profile_->get("frontTd"),
            profile_->flowPathTd(), profile_->get("idPrefixList"));
        if (!res) {
            delete tdsm_;
            tdsm_ = nullptr;
            onInfo("参数无效，请核对参数=");
            return;
        }

        // go...
        tdsm_thread_ = new QThread;
        tdsm_->moveToThread(tdsm_thread_);
        QObject::connect(tdsm_thread_, &QThread::started, tdsm_, &TdSm::start, Qt::QueuedConnection);
        QObject::connect(tdsm_thread_, &QThread::finished, tdsm_, &TdSm::deleteLater, Qt::QueuedConnection);
        QObject::connect(tdsm_thread_, &QThread::finished, tdsm_thread_, &QThread::deleteLater, Qt::QueuedConnection);
        QObject::connect(tdsm_, &TdSm::statusChanged, this, &MainWindow::onTdSmStateChanged, Qt::QueuedConnection);
        QObject::connect(tdsm_, &TdSm::info, this, &MainWindow::onInfo, Qt::QueuedConnection);
        QObject::connect(tdsm_, &TdSm::gotIds, this, &MainWindow::onGotIds, Qt::QueuedConnection);

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

    //设置行，按排序后合约来，一个合约一行=
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
    // input password
    LoginDialog dlg;
    if (!dlg.exec()) {
        return;
    }
    password_ = dlg.getPassword();

    // check
    if (mdsm_ != nullptr) {
        qFatal("mdsm_!= nullptr");
    }

    // init mdsm
    mdsm_ = new MdSm;
    bool res = mdsm_->init(profile_->get("userId"), password_,
        profile_->get("brokerId"), profile_->get("frontMd"), profile_->flowPathMd());
    if (!res) {
        delete mdsm_;
        mdsm_ = nullptr;
        onInfo("参数无效，请核对参数=");
        return;
    }

    // go...
    mdsm_thread_ = new QThread;
    mdsm_->moveToThread(mdsm_thread_);
    QObject::connect(mdsm_thread_, &QThread::started, mdsm_, &MdSm::start, Qt::QueuedConnection);
    QObject::connect(mdsm_thread_, &QThread::finished, mdsm_, &MdSm::deleteLater, Qt::QueuedConnection);
    QObject::connect(mdsm_thread_, &QThread::finished, mdsm_thread_, &QThread::deleteLater, Qt::QueuedConnection);
    QObject::connect(mdsm_, &MdSm::statusChanged, this, &MainWindow::onMdSmStateChanged, Qt::QueuedConnection);
    QObject::connect(mdsm_, &MdSm::info, this, &MainWindow::onInfo, Qt::QueuedConnection);
    QObject::connect(mdsm_, &MdSm::gotMdItem, this, &MainWindow::onGotMdItem, Qt::QueuedConnection);
    mdsm_thread_->start();

    //更新ui,接收数据中不要出现模态对话框=
    ui->actionStart->setEnabled(false);
    ui->actionConfig->setEnabled(false);
    ui->actionStop->setEnabled(true);
}

void MainWindow::on_actionStop_triggered()
{
    if (tdsm_) {
        tdsm_->stop();
    }

    if (mdsm_) {
        mdsm_->stop();
    }

    //更新ui
    ui->actionStart->setEnabled(true);
    ui->actionConfig->setEnabled(true);
    ui->actionStop->setEnabled(false);
}

void MainWindow::onGotMdItem(void* p)
{
    auto mdf = (DepthMarketDataField*)p;

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
    QString id = mdItem.value("InstrumentID").toString();
    int row = ids_row_.value(id);
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

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (mdsm_ || tdsm_) {
        this->hide();
        event->ignore();
    }
    else {
        event->accept();
    }
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(on_actionQuit_triggered()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    icon_ = QIcon(":/images/heart.png");
    trayIcon->setIcon(icon_);
    setWindowIcon(icon_);
    trayIcon->setToolTip("mdsrv");

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    trayIcon->setVisible(true);
    trayIcon->show();
}

void MainWindow::on_actionQuit_triggered()
{
    if (mdsm_ || tdsm_) {
        this->showNormal();
        onInfo("请先停止接收数据=");
        return;
    }

    qApp->quit();
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if (!this->isVisible())
            this->showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

//显示详细数据=
void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    TickForm* form = new TickForm();
    form->setWindowFlags(Qt::Window);
    form->Init(mdsm_, ui->tableWidget->item(row, 0)->text());
    form->show();
}
