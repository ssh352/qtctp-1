#ifndef MdSm_H
#define MdSm_H

#include <QObject>

class MdApi;
class MdSmSpi;

enum {
    MDSM_DISCONNECTED = 1,
    MDSM_CONNECTED,
    MDSM_LOGINED,
    MDSM_RECVING,
    MDSM_STOPPED
};

class MdSm : public QObject {
    Q_OBJECT
public:
    explicit MdSm(QObject* parent = 0);
    virtual ~MdSm();

public:
    static QString version();
    bool init(QString name, QString pwd, QString brokerId, QString front, QString flowPath);
    void start();
    void stop();
    void subscrible(QStringList ids);

signals:
    void statusChanged(int state);
    void runCmd(void* cmd);

protected:
    MdApi* mdapi() { return mdapi_; }
    QString brokerId() { return brokerId_; }
    QString userId() { return userId_; }
    QString password() { return password_; }
    void info(QString msg);

private:
    QString userId_,password_,brokerId_,frontMd_,flowPathMd_;
    MdApi* mdapi_ = nullptr;
    MdSmSpi* mdspi_ = nullptr;

    friend MdSmSpi;
};

#endif // MdSm_H
