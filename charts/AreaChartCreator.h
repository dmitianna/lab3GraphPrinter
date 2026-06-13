#ifndef AREACHARTCREATOR_H
#define AREACHARTCREATOR_H

#include "abstractchartcreator.h"

#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>

class AreaChartCreator : public AbstractChartCreator
{
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override
    {
        auto* upperSeries = new QLineSeries();
        for(const auto& point : data)
        {
            upperSeries->append(point.xAxis,point.yAxis);
        }
        auto* lowerSeries = new QLineSeries();
        for(const auto& point : data)
        {
            lowerSeries->append(point.xAxis,0);
        }
        return new QAreaSeries(upperSeries,lowerSeries);
    }

    QString getChartTitle() const override
    {
        return "Area Chart";
    }
};

#endif // AREACHARTCREATOR_H
