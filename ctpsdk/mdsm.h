#ifndef MdSm_H
#define MdSm_H

#include <QObject>
#include <QVariantMap>

class MdApi;

enum {
    MDSM_DISCONNECTED = 1,
    MDSM_CONNECTED,
    MDSM_LOGINED,
    MDSM_RECVING,
    MDSM_STOPPED
};

class MdSmSpi;
class MdSm : public QObject {
    Q_OBJECT
public:
    explicit MdSm(QObject* parent = 0);
    virtual ~MdSm();

public:
    void init(QString name, QString pwd, QString brokerId, QString front, QString flowPath);
    void start();
    void stop();
    void subscrible(QStringList ids);
    static QString version();

protected:
    MdApi* mdapi() { return mdapi_; }
    QString brokerId() { return brokerId_; }
    QString userId() { return name_; }
    QString password() { return pwd_; }

signals:
    void onStatusChanged(int state);
    void onInfo(QString msg);
    void onRunCmd(void* cmd);
    void onGotMd(QVariantMap mdItem);

private:
    QString name_;
    QString pwd_;
    QString brokerId_;
    QString front_;
    QString flowPath_;
    MdApi* mdapi_ = nullptr;
    MdSmSpi* mdspi_ = nullptr;

    friend MdSmSpi;
};

#endif // MdSm_H
