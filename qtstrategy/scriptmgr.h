#ifndef SCRIPTMGR_H
#define SCRIPTMGR_H

#include <QObject>
#include <QScriptValue>

class QScriptEngine;
class QScriptEngineDebugger;

class ScriptMgr : public QObject
{
    Q_OBJECT
public:
    explicit ScriptMgr(QObject *parent = 0);
    void init();
    void shutdown();
    void scriptText();
    void scriptHello();
    void scriptDebug();

signals:

public slots:

private:
    QScriptEngine* engine_ = nullptr;
    QScriptEngineDebugger* debugger_ = nullptr;
    QScriptValue scriptobj_;
};

#endif // SCRIPTMGR_H
