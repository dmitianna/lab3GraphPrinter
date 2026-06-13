#include "diconfiguration.h"
#include "charts/IChartCreator.h"
#include "charts/LineChartCreator.h"
#include "charts/AreaChartCreator.h"

IOCContainer gContainer;

void DIConfiguration::configure()
{
    switchToLineChart();
}

void DIConfiguration::switchToLineChart()
{
    gContainer.RegisterInstance<IChartCreator,LineChartCreator>();
}

void DIConfiguration::switchToAreaChart()
{
    gContainer.RegisterInstance<IChartCreator,AreaChartCreator>();
}
