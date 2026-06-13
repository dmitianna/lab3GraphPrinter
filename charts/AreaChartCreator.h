#ifndef AREACHARTCREATOR_H
#define AREACHARTCREATOR_H

#include "abstractchartcreator.h"
#include "ioc/diconfiguration.h"
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
        auto* areaSeries = new QAreaSeries(upperSeries,lowerSeries);
        if(DIConfiguration::isBlackWhite())
        {
            //areaSeries->setPen(QPen(Qt::NoPen));
            areaSeries->setBrush(QBrush(Qt::black));
        }
        return areaSeries;
    }

    QString getChartTitle() const override
    {
        return "Area Chart";
    }
};

#endif // AREACHARTCREATOR_H
