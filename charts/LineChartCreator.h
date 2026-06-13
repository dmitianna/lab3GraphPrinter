#ifndef LINECHARTCREATOR_H
#define LINECHARTCREATOR_H
#include <QDebug>
#include "abstractchartcreator.h"
#include <QtCharts/QLineSeries>
#include "ioc/diconfiguration.h"
class LineChartCreator : public AbstractChartCreator
{
protected:
    QAbstractSeries* createSeries(const QList<GraphData>& data) override
    {
        auto* series = new QLineSeries();
        QPen pen;
        if(DIConfiguration::isBlackWhite())
        {
            series->setPen(QPen(Qt::black));
        }
        else
        {
            pen.setColor(QColor(85,170,255)); // или любой нужный цвет
        }
        pen.setWidth(2);
        series->setPen(pen);
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
