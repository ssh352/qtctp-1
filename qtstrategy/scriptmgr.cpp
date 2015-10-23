#include "scriptmgr.h"
#include <QtScript>
#include <QScriptEngineDebugger>
#include "servicemgr.h"
#include "logger.h"

ScriptMgr::ScriptMgr(QObject *parent) : QObject(parent)
{

}

void ScriptMgr::init(){
    engine_ = new QScriptEngine;
    debugger_ = new QScriptEngineDebugger;
    debugger_->attachTo(engine_);

    QScriptValue loggerObj = engine_->newQObject(g_sm->logger());
    engine_->globalObject().setProperty("logger", loggerObj);

    QString fileName(":/helloscript.js");
    QFile scriptFile(fileName);
    scriptFile.open(QIODevice::ReadOnly);
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();

    scriptobj_ = engine_->evaluate(contents, fileName);
    if (scriptobj_.isError()) {
        g_sm->logger()->info(QString::fromLatin1("%0:%1: %2")
                              .arg(fileName)
                              .arg(scriptobj_.property("lineNumber").toInt32())
                              .arg(scriptobj_.toString()));
        return;
    }
}

void ScriptMgr::shutdown(){

    debugger_->detach();
    delete debugger_;
    delete engine_;
}

void ScriptMgr::scriptText(){
    g_sm->logger()->info(QString("scriptobj.text=") + scriptobj_.property("text").toString());
}

void ScriptMgr::scriptHello(){
    scriptobj_.property("run").call(scriptobj_);
}

void ScriptMgr::scriptDebug(){
    scriptobj_.property("debug").call(scriptobj_);
}
