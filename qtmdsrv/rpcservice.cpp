#include "rpcservice.h"
#include "qjsonrpctcpserver.h"

#include <QtCore/QDebug>

#include "servicemgr.h"
#include "logger.h"

TestRpcService::TestRpcService(QObject *parent)
    : QJsonRpcService(parent)
{
}

void TestRpcService::testMethod()
{
    qDebug() << Q_FUNC_INFO << "called" << endl;
}

void TestRpcService::testMethodWithParams(const QString &first, bool second, double third)
{
    qDebug() << Q_FUNC_INFO << "called with parameters: " << endl
             << " first: " << first << endl
             << "second: " << second << endl
             << " third: " << third << endl;
}

void TestRpcService::testMethodWithVariantParams(const QString &first, bool second, double third, const QVariant &fourth)
{
    qDebug() << Q_FUNC_INFO << "called with variant parameters: " << endl
             << " first: " << first << endl
             << "second: " << second << endl
             << " third: " << third << endl
             << "fourth: " << fourth << endl;
}

QString TestRpcService::testMethodWithParamsAndReturnValue(const QString &name)
{
    qDebug() << Q_FUNC_INFO << "called" << endl;
    return QString("Hello %1").arg(name);
}

void TestRpcService::testMethodWithDefaultParameter(const QString &first, const QString &second)
{
    qDebug() << Q_FUNC_INFO << endl
             << "first: " << first << endl
             << (second.isEmpty() ? "not defined, default parameter" : second) << endl;
}

RpcService::RpcService(QObject *parent) : QObject(parent)
{

}

void RpcService::init(){
    g_sm->logger()->info(__FUNCTION__);
    rpcServer_ = new QJsonRpcTcpServer;//QJsonRpcHttpServer;
    rpcServer_->addService(new TestRpcService);
    if (!rpcServer_->listen(QHostAddress::LocalHost, 5555)) {
        qDebug() << "can't start tcp server: " << rpcServer_->errorString();
        return;
    }
}

void RpcService::shutdown(){
    g_sm->logger()->info(__FUNCTION__);
    rpcServer_->close();
    delete rpcServer_;
    rpcServer_ = nullptr;
}
