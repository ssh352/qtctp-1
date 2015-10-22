#ifndef RPCSERVICE_H
#define RPCSERVICE_H

#include <QObject>
#include "qjsonrpcservice.h"

class TestRpcService : public QJsonRpcService
{
    Q_OBJECT
    Q_CLASSINFO("serviceName", "agent")
public:
    TestRpcService(QObject *parent = 0);

public Q_SLOTS:
    void testMethod();
    void testMethodWithParams(const QString &first, bool second, double third);
    void testMethodWithVariantParams(const QString &first, bool second, double third, const QVariant &fourth);
    QString testMethodWithParamsAndReturnValue(const QString &name);
    void testMethodWithDefaultParameter(const QString &first, const QString &second = QString());

};

class QJsonRpcTcpServer;
class RpcService : public QObject
{
    Q_OBJECT
public:
    explicit RpcService(QObject *parent = 0);
    void init();
    void shutdown();

signals:

public slots:

private:
    QJsonRpcTcpServer* rpcServer_ = nullptr;
};

#endif // RPCSERVICE_H
