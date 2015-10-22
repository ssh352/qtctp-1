#ifndef SERVICEMGR_H
#define SERVICEMGR_H

#include <QObject>

class Logger;
class Profile;
class CtpCmdMgr;
class CtpMgr;
class DataPump;
class RpcService;
class PushService;

class ServiceMgr : public QObject {
    Q_OBJECT
public:
    explicit ServiceMgr(QObject* parent = 0);
    void init();
    void shutdown();

public:
    Logger* logger();
    Profile* profile();
    CtpCmdMgr* ctpCmdMgr();
    CtpMgr* ctpMgr();
    DataPump* dataPump();
    RpcService* rpcService();
    PushService* pushService();

signals:

public slots:

private:
    void check();

private:
    Logger* logger_ = nullptr;
    Profile* profile_ = nullptr;
    CtpCmdMgr* ctpCmdMgr_ = nullptr;
    CtpMgr* ctpMgr_ = nullptr;
    DataPump* dataPump_ = nullptr;
    RpcService* rpcService_ = nullptr;
    PushService* pushService_ = nullptr;

    bool shutdown_ = false;
    bool init_ = false;
};

extern ServiceMgr* g_sm;

#endif // SERVICEMGR_H
