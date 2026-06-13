#ifndef DATEEXTRACTER_H
#define DATEEXTRACTER_H
#include "IDataExtracter.h"
#include "QDate"
class DateExtracter : public IDataExtracter<QDateTime>
{
public:
    QDateTime extract(const QString& raw) const override;
};
#endif // DATEEXTRACTER_H
