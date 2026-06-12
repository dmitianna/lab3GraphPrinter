#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QObject>
#include <QList>
#include "GraphData.h"

class DataModel : public QObject
{
    Q_OBJECT

public:
    explicit DataModel(QObject* parent = nullptr);
    QList<GraphData> getData() const;
    void setData(const QList<GraphData>& data);

signals:
    void dataChanged();

private:
    QList<GraphData> _data;
};
#endif // DATAMODEL_H
