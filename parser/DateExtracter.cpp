#include "DateExtracter.h"

GraphData DateExtracter::extract(const QStringList& rowData) const
{
    GraphData result;
    result.xAxis = 0;
    result.yAxis = rowData[1].toDouble();
    return result;
}
