#ifndef CTPCMDMGR_H
#define CTPCMDMGR_H

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

    void init();
    void shutdown();

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
    TraderApi* tdapi_ = nullptr;
    MdApi* mdapi_ = nullptr;
    QQueue<CtpCmd*> cmds_;
    int interval_ = 100;
    int timer_id_ = -1;
};


#endif // CTPCMDMGR_H
