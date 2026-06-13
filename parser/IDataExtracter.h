#ifndef IDATAEXTRACTER_H
#define IDATAEXTRACTER_H
#include <QString>
template<typename T>
class IDataExtracter
{
public:
    virtual ~IDataExtracter() = default;
    virtual T extract(const QString& raw) const = 0;
};
#endif // IDATAEXTRACTER_H
