#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class Profile;
class Logger;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    void shutdown();

public slots:
    void onInfo(QString msg);

private slots:
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_actionQuit_triggered();
    void on_actionVersion_triggered();

    void on_actionPureCallCrash_triggered();
    void on_actionInvalidParamCrash_triggered();
    void on_actionDerefZeroCrash_triggered();
    void on_actionQFatal_triggered();
    void on_actionDebugbreak_triggered();
    void on_actionDebugBreak_triggered();
    void on_actionExit_triggered();
    void on_actionExitProcess_triggered();
    void on_actionTerminateProcess_triggered();

    void on_actionHello_triggered();
    void on_actionText_triggered();
    void on_actionDebug_triggered();

private:
    void closeEvent (QCloseEvent *event) override;
    void createTrayIcon();
    void createActions();
    Profile* profile();
    Logger* logger();

private:
    Ui::MainWindow *ui;

private:
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QIcon icon_;
};

#endif // MAINWINDOW_H
