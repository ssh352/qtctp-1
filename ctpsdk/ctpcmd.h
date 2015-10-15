#ifndef CTPCMD_H
#define CTPCMD_H

#include <QObject>
#include <QQueue>

class MdApi;
class TraderApi;
class CtpCmd;

//统一管理和派发信号=
class CtpCmdMgr : public QObject {
    Q_OBJECT
public:
    explicit CtpCmdMgr(QObject* parent = 0);
    virtual ~CtpCmdMgr()
    {
        stop();
        if (cmds_.length() != 0) {
            qFatal("cmds_length() != 0");
        }
        this_ = nullptr;
    }
    static CtpCmdMgr* instance()
    {
        if (this_ == nullptr) {
            qFatal("this_ == nullptr");
        }
        return this_;
    }

    void setInterval(int ms) { interval_ = ms; }
    void start() { timer_id_ = startTimer(interval_); }
    void stop()
    {
        if (timer_id_ != -1)
            killTimer(timer_id_);
        timer_id_ = -1;
    }

    void setTdApi(TraderApi* tdapi) { tdapi_ = tdapi; }
    void setMdApi(MdApi* mdapi) { mdapi_ = mdapi; }
    MdApi* mdapi() { return mdapi_; }
    TraderApi* tdapi() { return tdapi_; }

signals:
    void onInfo(QString msg);

public slots:
    void onRunCmd(void* p)
    {
        CtpCmd* cmd = (CtpCmd*)p;
        cmds_.append(cmd);
    }

private:
    void timerEvent(QTimerEvent* event) override
    {
        runNow();
    }
    //取第一个然后执行，如果网络限制，就留着下次执行-
    void runNow();

private:
    static CtpCmdMgr* this_;
    TraderApi* tdapi_ = nullptr;
    MdApi* mdapi_ = nullptr;
    QQueue<CtpCmd*> cmds_;
    int interval_ = 100;
    int timer_id_ = -1;
};

class CtpCmd {
public:
    explicit CtpCmd() {}
    virtual ~CtpCmd() {}
    void runNow()
    {
        //初始化id，确保在run线程上对id做操作
        resetId();
        run();
    }
    int reqId()
    {
        return reqId_;
    }
    void resetId()
    {
        reqId_ = g_reqId_;
        g_reqId_++;
    }
    int result()
    {
        return result_;
    }
    TraderApi* tdapi()
    {
        return CtpCmdMgr::instance()->tdapi();
    }
    MdApi* mdapi()
    {
        return CtpCmdMgr::instance()->mdapi();
    }
    void info(QString msg)
    {
        emit CtpCmdMgr::instance()->onInfo(msg);
    }

    static void setIdSeed(int idSeed)
    {
        g_reqId_ = idSeed;
    }

protected:
    virtual void run() {}

protected:
    int reqId_ = 0;
    int result_ = 0;
    static int g_reqId_;
};

class CmdMdLogin : public CtpCmd {
public:
    explicit CmdMdLogin(QString username, QString password, QString brokerId)
        : CtpCmd()
        , userName_(username)
        , password_(password)
        , brokerId_(brokerId)
    {
    }

    void run() override;

private:
    QString userName_, password_, brokerId_;
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
    explicit CmdTdLogin(QString username, QString password, QString brokerId)
        : CtpCmd()
        , userName_(username)
        , password_(password)
        , brokerId_(brokerId)
    {
    }

    void run() override;

private:
    QString userName_, password_, brokerId_;
};

class CmdTdLogout : public CtpCmd {
public:
    explicit CmdTdLogout(QString username, QString brokerId)
        : CtpCmd()
        , userName_(username)
        , brokerId_(brokerId)
    {
    }

    void run() override;

private:
    QString userName_, brokerId_;
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
