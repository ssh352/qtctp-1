#pragma once

#include <QString>

#include "ApiStruct.h"

bool extractQrcFile(QString qrc_file, QString local_file);

struct TickItem{
    double LastPrice;
    double BidPrice1;
    int BidVolume1;
    double AskPrice1;
    int AskVolume1;
    int Volume;
    double OpenInterest;
};

struct BarItem{
    double OpenPrice;
    double ClosePrice;
    double HighestPrice;
    double LowestPrice;
    int Volume;
    double OpenInterest;
};
