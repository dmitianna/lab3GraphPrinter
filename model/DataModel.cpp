#include "DataModel.h"

QList<GraphData> DataModel::getData() const
{
    return _data;
}

void DataModel::setData(const QList<GraphData>& data)
{
    _data = data;
    emit dataChanged();
}
