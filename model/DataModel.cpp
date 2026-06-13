#include "DataModel.h"

#include "DataModel.h"

DataModel::DataModel(QObject* parent): QObject(parent)
{
}
QList<GraphData> DataModel::getData() const
{
    return _data;
}

void DataModel::setData(const QList<GraphData>& data)
{
    _data = data;
    emit dataChanged();
}
