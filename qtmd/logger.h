#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = 0);
    void init();
    void shutdown();

signals:
    void info(QString msg);
};

#endif // LOGGER_H
