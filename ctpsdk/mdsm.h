#ifndef MdSm_H
#define MdSm_H

#include <QObject>
#include <QMap>

class MdApi;
class MdSmSpi;
class RingBuffer;

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
    bool init(QString name, QString pwd, QString brokerId, QString front, QString flowPath);
    void start();
    void stop();
    void subscrible(QStringList ids);
    RingBuffer* getRingBuffer(QString id);
    int ringBufferLen() { return ringBufferLen_; }
    static QString version();

signals:
    void statusChanged(int state);
    void info(QString msg);
    void runCmd(void* cmd);
    void gotMdItem(void* mdItem, int indexRb);

protected:
    MdApi* mdapi() { return mdapi_; }
    QString brokerId() { return brokerId_; }
    QString userId() { return userId_; }
    QString password() { return password_; }

private:
    void initRb(QStringList ids);
    void freeRb();
    void* saveRb(void* mdItem, int& indexRb);

private:
    QString userId_,password_,brokerId_,frontMd_,flowPathMd_;
    MdApi* mdapi_ = nullptr;
    MdSmSpi* mdspi_ = nullptr;
    QMap<QString, RingBuffer*> rbs_;
    const int ringBufferLen_ = 256;

    friend MdSmSpi;
};

#endif // MdSm_H
