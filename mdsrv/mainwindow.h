#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariantMap>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class QThread;
class MdSm;
class TdSm;
class CtpCmdMgr;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void onMdSmStateChanged(int state);
    void onTdSmStateChanged(int state);
    void onInfo(QString msg);
    void onGotIds(QStringList ids);
    void onGotMdItem(void* item);

private slots:
    void on_actionAbout_triggered();
    void on_actionConfig_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionQuit_triggered();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    void loadCfg();
    void closeEvent (QCloseEvent *event) override;
    void createTrayIcon();
    void createActions();

private:
    Ui::MainWindow* ui;
    MdSm* mdsm_ = nullptr;
    QThread* mdsm_thread_ = nullptr;
    TdSm* tdsm_ = nullptr;
    QThread* tdsm_thread_ = nullptr;
    QString userName_,password_,brokerId_,frontTd_,frontMd_,subscribleIds_;
    CtpCmdMgr *cmdmgr_;
    QMap<QString,int> ids_row_;
    QStringList ids_col_;

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
