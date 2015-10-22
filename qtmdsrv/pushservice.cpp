#include "pushservice.h"

#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QtCore/QDebug>

TestPushService::TestPushService(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR),
    m_clients()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("TestPushService"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Chat Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &TestPushService::onNewConnection);
    }
}

TestPushService::~TestPushService()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void TestPushService::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &TestPushService::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &TestPushService::socketDisconnected);

    m_clients << pSocket;
}

void TestPushService::processMessage(QString message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    Q_FOREACH (QWebSocket *pClient, m_clients)
    {
        if (pClient != pSender) //don't echo message back to sender
        {
            pClient->sendTextMessage(message);
        }
    }
}

void TestPushService::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}


PushService::PushService(QObject *parent) : QObject(parent)
{

}

void PushService::init(){
    pushService_ = new TestPushService(1234);
}

void PushService::shutdown(){
    delete pushService_;
}
