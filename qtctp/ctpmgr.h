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
    MdSm* mdsm(){return mdsm_;}
    void subscrible(QStringList ids);

signals:
    void gotIds(QStringList ids);
    void mdStopped();
    void mdDisconnect();

private slots:
    void onMdSmStateChanged(int state);
    void onTdSmStateChanged(int state);
    void onGotIds(QStringList ids);

private:
    Profile* profile();
    Logger* logger();

private:
    MdSm* mdsm_ = nullptr;
    QThread* mdsm_thread_ = nullptr;
    TdSm* tdsm_ = nullptr;
    QThread* tdsm_thread_ = nullptr;

    QString password_;
};

#endif // CTPMGR_H
