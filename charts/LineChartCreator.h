#ifndef LINECHARTCREATOR_H
#define LINECHARTCREATOR_H

#include "abstractchartcreator.h"
#include <QtCharts/QLineSeries>

class LineChartCreator : public AbstractChartCreator
{
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override
    {
        auto* series = new QLineSeries();
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
