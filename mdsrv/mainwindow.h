#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_actionAbout_triggered();
    void on_actionConfig_triggered();
    void on_actionExit_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();

private:
    void loadCfg();

private:
    Ui::MainWindow* ui;
    MdSm* mdsm_ = nullptr;
    QThread* mdsm_thread_ = nullptr;
    TdSm* tdsm_ = nullptr;
    QThread* tdsm_thread_ = nullptr;
    QString userName_,password_,brokerId_,frontTd_,frontMd_,subscribleIds_;
    CtpCmdMgr *cmdmgr_;

};

#endif // MAINWINDOW_H
