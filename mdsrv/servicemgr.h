#ifndef SERVICEMGR_H
#define SERVICEMGR_H

#include <QObject>

class Profile;

class ServiceMgr : public QObject {
    Q_OBJECT
public:
    explicit ServiceMgr(QObject* parent = 0);
    void init();
    void shutdown();
    bool died();

public:
    Profile* profile();

signals:

public slots:

private:
    Profile* profile_ = nullptr;
    bool shutdown_ = false;
};

extern ServiceMgr* g_sm;

#endif // SERVICEMGR_H
