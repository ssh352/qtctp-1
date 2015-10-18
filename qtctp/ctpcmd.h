#ifndef CTPCMD_H
#define CTPCMD_H

#include <QObject>

class MdApi;
class TraderApi;
class CtpCmd;
class Logger;

class CtpCmd {
public:
    explicit CtpCmd() {}
    virtual ~CtpCmd() {}
    void runNow()
    {
        //初始化id，确保在run线程上对id做操作=
        resetId();
        run();
    }
    int reqId() { return reqId_; }
    void resetId()
    {
        reqId_ = g_reqId_;
        g_reqId_++;
    }
    int result() { return result_; }
    TraderApi* tdapi();
    MdApi* mdapi();
    void info(QString msg);

public:
    static void setIdSeed(int idSeed) { g_reqId_ = idSeed; }

protected:
    virtual void run() {}

protected:
    int reqId_ = 0;
    int result_ = 0;
    static int g_reqId_;
};

class CmdMdLogin : public CtpCmd {
public:
    explicit CmdMdLogin(QString userId, QString password, QString brokerId)
        : CtpCmd()
        , userId_(userId)
        , password_(password)
        , brokerId_(brokerId)
    {
    }

    void run() override;

private:
    QString userId_, password_, brokerId_;
};

class CmdMdSubscrible : public CtpCmd {
public:
    explicit CmdMdSubscrible(QStringList ids)
        : CtpCmd()
        , ids_(ids)
    {
    }
    void run() override;

private:
    QStringList ids_;
};

class CmdTdLogin : public CtpCmd {
public:
    explicit CmdTdLogin(QString userId, QString password, QString brokerId)
        : CtpCmd()
        , userId_(userId)
        , password_(password)
        , brokerId_(brokerId)
    {
    }
    void run() override;

private:
    QString userId_, password_, brokerId_;
};

class CmdTdLogout : public CtpCmd {
public:
    explicit CmdTdLogout(QString userId, QString brokerId)
        : CtpCmd()
        , userId_(userId)
        , brokerId_(brokerId)
    {
    }
    void run() override;

private:
    QString userId_, brokerId_;
};

class CmdTdQueryInstrument : public CtpCmd {
public:
    explicit CmdTdQueryInstrument()
        : CtpCmd()
    {
    }
    void run() override;

private:
};

#endif // CTPCMD_H
