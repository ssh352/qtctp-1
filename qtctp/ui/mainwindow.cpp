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
#include "logger.h"
#include "ctpmgr.h"
#include "datapump.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // main window
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 1);
    setWindowTitle("qtctp");
    icon_ = QIcon(":/images/heart.png");
    setWindowIcon(icon_);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    // logger
    QObject::connect(logger(), &Logger::info, this, &MainWindow::onInfo);
    // ctpmgr
    QObject::connect(g_sm->ctpMgr(), &CtpMgr::gotIds, this, &MainWindow::onGotIds);
    QObject::connect(g_sm->dataPump(), &DataPump::gotMdItem, this, &MainWindow::onGotMdItem);
}

void MainWindow::shutdown()
{
}

void MainWindow::onInfo(QString msg)
{
    ui->listWidget->addItem(msg);
    //滚动到最后一行=
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

void MainWindow::onGotIds(QStringList ids)
{
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
}

void MainWindow::on_actionVersion_triggered()
{
    logger()->info(QString("qtctp version: ") + QString(__DATE__) +" " + QString(__TIME__));
    logger()->info(QString("mdapi version: ") + MdSm::version());
    logger()->info(QString("tdapi version: ") + TdSm::version());
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
    QString password = dlg.getPassword();

    //start
    if (!g_sm->ctpMgr()->start(password)) {
        return;
    }

    //更新ui,接收数据中不要出现模态对话框=
    ui->actionStart->setEnabled(false);
    ui->actionConfig->setEnabled(false);
    ui->actionStop->setEnabled(true);
}

void MainWindow::on_actionStop_triggered()
{
    //stop
    g_sm->ctpMgr()->stop();

    //更新ui
    ui->actionStart->setEnabled(true);
    ui->actionConfig->setEnabled(true);
    ui->actionStop->setEnabled(false);
}

void MainWindow::onGotMdItem(void* p, int indexRb, void* rb)
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
    if (g_sm->ctpMgr()->running()) {
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
    trayIcon->setIcon(icon_);
    trayIcon->setToolTip("mdsrv");

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    trayIcon->setVisible(true);
    trayIcon->show();
}

void MainWindow::on_actionQuit_triggered()
{
    if (g_sm->ctpMgr()->running()) {
        this->showNormal();
        logger()->info("请先停止接收数据=");
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
    form->Init(ui->tableWidget->item(row, 0)->text());
    form->show();
}

Profile* MainWindow::profile()
{
    return g_sm->profile();
}

Logger* MainWindow::logger()
{
    return g_sm->logger();
}

void MainWindow::on_actionInvalidParamCrash_triggered()
{
    //InvalidParamCrash
    printf(nullptr);
}

void MainWindow::on_actionPureCallCrash_triggered()
{
    //PureCallCrash
    base::debug::Derived derived;
    base::debug::Alias(&derived);
}

void MainWindow::on_actionDerefZeroCrash_triggered()
{
    //DerefZeroCrash
    int* x = 0;
    *x = 1;
    base::debug::Alias(x);
}
