#ifndef DATAPUMP_H
#define DATAPUMP_H

#include <QObject>
#include <QStringList>
#include <QMap>

class RingBuffer;

class DataPump : public QObject {
    Q_OBJECT
public:
    explicit DataPump(QObject* parent = 0);
    void init();
    void shutdown();
    void put(void* mdItem);
    RingBuffer* getRingBuffer(QString id);
    void freeRb();
    void initRb(QStringList ids);

signals:
    void gotMdItem(void* mdItem, int indexRb, void* rb);

public slots:

private:
    void* saveRb(void* mdItem, int& indexRb, RingBuffer*& rb);
    void fixTickMs(void* mdItem, int indexRb, RingBuffer* rb);

private:
    QMap<QString, RingBuffer*> rbs_;
    const int ringBufferLen_ = 256;
};

#endif // DATAPUMP_H
