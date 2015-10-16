#ifndef MdSm_H
#define MdSm_H

#include <QObject>
#include <QMap>

class MdApi;
class MdSmSpi;
class MdRingBuffer;

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
    void init(QString name, QString pwd, QString brokerId, QString front, QString flowPath);
    void start();
    void stop();
    void subscrible(QStringList ids);
    int getMdItemHead(QString id);
    void* getMdItem(QString id, int index);
    int ringBufferLen() { return ringbuffer_len; }
    static QString version();

protected:
    MdApi* mdapi() { return mdapi_; }
    QString brokerId() { return brokerId_; }
    QString userId() { return name_; }
    QString password() { return pwd_; }

private:
    void initRb(QStringList ids);
    void freeRb();
    void* saveRb(void* mdItem, int& index);

signals:
    void statusChanged(int state);
    void info(QString msg);
    void runCmd(void* cmd);
    void gotMdItem(void* mdItem, int indexRb);

private:
    QString name_;
    QString pwd_;
    QString brokerId_;
    QString front_;
    QString flowPath_;
    MdApi* mdapi_ = nullptr;
    MdSmSpi* mdspi_ = nullptr;
    QMap<QString, MdRingBuffer*> rbs_;
    const int ringbuffer_len = 256;

    friend MdSmSpi;
};

#endif // MdSm_H
