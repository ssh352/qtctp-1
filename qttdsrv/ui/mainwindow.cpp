#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servicemgr.h"
#include "profile.h"
#include "logger.h"
#include "utils.h"
#include <windows.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(Profile::appName());
    icon_ = QIcon(":/images/heart.png");
    setWindowIcon(icon_);

    //设置trayicon
    this->createActions();
    this->createTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    // logger
    QObject::connect(logger(), &Logger::gotInfo, this, &MainWindow::onInfo);
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

void MainWindow::on_actionVersion_triggered()
{
    logger()->info(QString("app version: ") + QString(__DATE__) + " " + QString(__TIME__));
}

void MainWindow::on_actionQuit_triggered()
{
    Logger::stopExitMonitor();
    qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    this->hide();
    event->ignore();
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
    trayIcon->setToolTip(Profile::appName());

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    trayIcon->setVisible(true);
    trayIcon->show();
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

void MainWindow::on_actionQFatal_triggered()
{
    qFatal("crash for qFatal");
}

void MainWindow::on_actionDebugbreak_triggered()
{
    __debugbreak();
}

void MainWindow::on_actionDebugBreak_triggered()
{
    DebugBreak();
}


void MainWindow::on_actionExit_triggered()
{
    exit(1);
}

void MainWindow::on_actionExitProcess_triggered()
{
    ::ExitProcess(1);
}

void MainWindow::on_actionTerminateProcess_triggered()
{
    ::TerminateProcess(::GetCurrentProcess(),1);
}
