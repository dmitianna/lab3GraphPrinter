#include "diconfiguration.h"
#include "charts/IChartCreator.h"
#include "charts/LineChartCreator.h"
#include "charts/AreaChartCreator.h"
static bool g_blackWhite = false;
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

void DIConfiguration::setBlackWhite(bool enabled)
{
    g_blackWhite = enabled;
}

bool DIConfiguration::isBlackWhite()
{
    return g_blackWhite;
}
