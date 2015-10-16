#ifndef TdSm_H
#define TdSm_H

#include <QObject>

class TraderApi;

enum {
    TDSM_DISCONNECTED = 1,
    TDSM_CONNECTED,
    TDSM_LOGINED,
    TDSM_RECVING,
    TDSM_LOGOUTED,
    TDSM_STOPPED
};

class TdSmSpi;
class TdSm : public QObject {
    Q_OBJECT
public:
    explicit TdSm(QObject* parent = 0);
    virtual ~TdSm();

public:
    void init(QString name, QString pwd, QString brokerId, QString front, QString flowPath,QString ids);
    void start();
    void logout();
    void stop();
    static QString version();

protected:
    TraderApi* tdapi() { return tdapi_; }
    QString brokerId(){return brokerId_;}
    QString userId(){return name_;}
    QString password(){return pwd_;}
    QString idFilters(){return ids_;}

signals:
    void onStatusChanged(int state);
    void onInfo(QString msg);
    void onGotIds(QStringList ids);
    void onRunCmd(void* cmd);

private:
    QString name_;
    QString pwd_;
    QString brokerId_;
    QString front_;
    QString flowPath_;
    QString ids_;
    TraderApi* tdapi_ = nullptr;
    TdSmSpi* tdspi_ = nullptr;

    friend TdSmSpi;
};

#endif // TdSm_H
