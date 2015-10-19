#include "datapump.h"
#include "ringbuffer.h"
#include "ApiStruct.h"

DataPump::DataPump(QObject* parent)
    : QObject(parent)
{
}

void DataPump::init()
{
}

void DataPump::shutdown()
{
}

//在spi线程上直接调用=
void DataPump::put(void* mdItem)
{
    int indexRb = -1;
    RingBuffer* rb = nullptr;
    void* item = this->saveRb(mdItem, indexRb, rb);
    fixTickMs(item, indexRb, rb);

    emit this->gotMdItem(item, indexRb, rb);
}

//在ctpmgr线程上
void DataPump::initRb(QStringList ids)
{
    if (rbs_.count()) {
        freeRb();
    }

    for (int i = 0; i < ids.count(); i++) {
        QString id = ids.at(i);
        RingBuffer* rb = new RingBuffer;
        rb->init(sizeof(DepthMarketDataField), ringBufferLen_);
        rbs_.insert(id, rb);
    }
}

//在ctpmgr线程上
void DataPump::freeRb()
{
    auto rb_list = rbs_.values();
    for (int i = 0; i < rb_list.length(); i++) {
        RingBuffer* rb = rb_list.at(i);
        rb->free();
        delete rb;
    }
    rbs_.clear();
}

void* DataPump::saveRb(void* mdItem, int& index, RingBuffer*& rb)
{
    DepthMarketDataField* mdf = (DepthMarketDataField*)mdItem;
    QString id = mdf->InstrumentID;
    rb = rbs_.value(id);
    if (rb == nullptr) {
        qFatal("rb == nullptr");
    }

    return rb->put(mdItem, index);
}

RingBuffer* DataPump::getRingBuffer(QString id)
{
    return rbs_.value(id);
}

// 和前一个tick比较，如果time相同，就改ms为前一个的ms+1，不同，ms改为0
void DataPump::fixTickMs(void* mdItem, int indexRb, RingBuffer* rb)
{  
    DepthMarketDataField* preItem = nullptr;
    DepthMarketDataField* curItem = (DepthMarketDataField*)mdItem;
    int index = indexRb - 1;
    if (index < 0) {
        index = index + rb->count();
    }
    preItem = (DepthMarketDataField*)rb->get(index);
    if (preItem && strcmp(curItem->UpdateTime,preItem->UpdateTime)== 0) {
        curItem->UpdateMillisec = preItem->UpdateMillisec + 1;
    }else{
        curItem->UpdateMillisec = 0;
    }
}
