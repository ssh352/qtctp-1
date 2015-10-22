#ifndef CTPMGR_H
#define CTPMGR_H

#include <QObject>
class Profile;
class Logger;
class TdSm;
class MdSm;

class CtpMgr : public QObject
{
    Q_OBJECT
public:
    explicit CtpMgr(QObject *parent = 0);
    void init();
    void shutdown();

    bool start(QString password);
    void stop();
    bool running();

signals:
    void gotInstruments(QStringList ids);
    void mdStopped();
    void mdDisconnect();

private slots:
    void onMdSmStateChanged(int state);
    void onTdSmStateChanged(int state);
    void onGotInstruments(QStringList ids);

private:
    Profile* profile();
    Logger* logger();
    bool initMdSm();
    void startMdSm();
    bool initTdSm();
    void startTdSm();
    void tryStartSubscrible();

private:
    MdSm* mdsm_ = nullptr;
    QThread* mdsm_thread_ = nullptr;
    bool mdsm_logined_ = false;
    TdSm* tdsm_ = nullptr;
    QThread* tdsm_thread_ = nullptr;
    bool tdsm_logined_ = false;
    bool autoLoginTd_ = true;
    bool autoLoginMd_ = true;

    QString password_;
};

#endif // CTPMGR_H
