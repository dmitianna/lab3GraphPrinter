#ifndef DATEEXTRACTER_H
#define DATEEXTRACTER_H
#include "IDataExtracter.h"
class DateExtracter : public IDataExtracter
{
public:
    GraphData extract(const QStringList& rowData) const override;
};
#endif // DATEEXTRACTER_H
