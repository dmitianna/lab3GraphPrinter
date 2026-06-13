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
};

#endif // DICONFIGURATION_H
