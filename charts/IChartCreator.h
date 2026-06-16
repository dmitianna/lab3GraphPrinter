#ifndef ICHARTCREATOR_H
#define ICHARTCREATOR_H
#include <QtCharts/QChart>
#include "model/GraphData.h"

QT_CHARTS_USE_NAMESPACE
class IChartCreator
{
public:
    virtual ~IChartCreator() = default;
    virtual QChart* create(const QList<GraphData>& data) = 0;
};

#endif // ICHARTCREATOR_H
