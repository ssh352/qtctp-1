#ifndef TdSm_H
#define TdSm_H

#include <QObject>

class TraderApi;

enum {
    TDSM_DISCONNECTED = 1,
    TDSM_CONNECTED,
    TDSM_LOGINED,
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
    static QString version();
    bool init(QString userId, QString password, QString brokerId, QString frontTd, QString flowPathTd,QString idPrefixList);
    void start();
    void logout();
    void stop();
    void queryInstrument();

signals:
    void statusChanged(int state);
    void gotInstruments(QStringList ids);
    void runCmd(void* cmd);

protected:
    TraderApi* tdapi() { return tdapi_; }
    QString brokerId(){return brokerId_;}
    QString userId(){return userId_;}
    QString password(){return password_;}
    QString idPrefixList(){return idPrefixList_;}
    void info(QString msg);

private:
    QString userId_,password_,brokerId_,frontTd_,flowPathTd_,idPrefixList_;
    TraderApi* tdapi_ = nullptr;
    TdSmSpi* tdspi_ = nullptr;

    friend TdSmSpi;
};

#endif // TdSm_H
