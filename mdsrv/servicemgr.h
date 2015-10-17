#ifndef SERVICEMGR_H
#define SERVICEMGR_H

#include <QObject>

class Profile;
class Logger;
class CtpCmdMgr;
class CtpMgr;

class ServiceMgr : public QObject {
    Q_OBJECT
public:
    explicit ServiceMgr(QObject* parent = 0);
    void init();
    void shutdown();

public:
    Profile* profile();
    Logger* logger();
    CtpCmdMgr* ctpCmdMgr();
    CtpMgr* ctpMgr();

signals:

public slots:

private:
    void check();

private:
    Profile* profile_ = nullptr;
    Logger* logger_ = nullptr;
    CtpCmdMgr* ctpCmdMgr_ = nullptr;
    CtpMgr* ctpMgr_ = nullptr;

    bool shutdown_ = false;
    bool init_ = false;
};

extern ServiceMgr* g_sm;

#endif // SERVICEMGR_H
