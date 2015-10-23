#ifndef SERVICEMGR_H
#define SERVICEMGR_H

#include <QObject>

class Logger;
class Profile;
class ScriptMgr;

class ServiceMgr : public QObject {
    Q_OBJECT
public:
    explicit ServiceMgr(QObject* parent = 0);
    void init();
    void shutdown();

public:
    Logger* logger();
    Profile* profile();
    ScriptMgr* scriptMgr();

signals:

public slots:

private:
    void check();

private:
    Logger* logger_ = nullptr;
    Profile* profile_ = nullptr;
    ScriptMgr* scriptMgr_ = nullptr;

    bool shutdown_ = false;
    bool init_ = false;
};

extern ServiceMgr* g_sm;

#endif // SERVICEMGR_H
