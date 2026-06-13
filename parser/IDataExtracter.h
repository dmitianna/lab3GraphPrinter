#ifndef IDATAEXTRACTER_H
#define IDATAEXTRACTER_H
#include "model/GraphData.h"
#include "QStringList"
class IDataExtracter
{
public:
    virtual ~IDataExtracter() = default;
    virtual GraphData extract(const QStringList& rowData) const = 0;
};
#endif // IDATAEXTRACTER_H
