#ifndef LINECHARTCREATOR_H
#define LINECHARTCREATOR_H

#include "abstractchartcreator.h"
#include <QtCharts/QLineSeries>
#include "ioc/diconfiguration.h"
class LineChartCreator : public AbstractChartCreator
{
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override
    {
        auto* series = new QLineSeries();
        if(DIConfiguration::isBlackWhite())
        {
            series->setPen(QPen(Qt::black));
        }
        for(const auto& point : data)
        {
            series->append(point.xAxis,point.yAxis);
        }
        return series;
    }

    QString getChartTitle() const override
    {
        return "Line Chart";
    }
};

#endif // LINECHARTCREATOR_H
