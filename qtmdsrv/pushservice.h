#ifndef PUSHSERVICE_H
#define PUSHSERVICE_H

#include <QObject>

class QWebSocketServer;
class QWebSocket;

class TestPushService : public QObject
{
    Q_OBJECT
public:
    explicit TestPushService(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~TestPushService();

private Q_SLOTS:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

class PushService : public QObject
{
    Q_OBJECT
public:
    explicit PushService(QObject *parent = 0);
    void init();
    void shutdown();

signals:

public slots:

private:
    TestPushService* pushService_ = nullptr;
};

#endif // PUSHSERVICE_H
