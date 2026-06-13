#ifndef DICONFIGURATION_H
#define DICONFIGURATION_H
#include "IOC_Contaner.h"

extern IOCContainer gContainer;

class DIConfiguration
{
public:
    static void configure();
    static void switchToLineChart();
    static void switchToAreaChart();

    static void setBlackWhite(bool enabled);
    static bool isBlackWhite();
};

#endif // DICONFIGURATION_H
