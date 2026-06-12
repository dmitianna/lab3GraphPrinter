#ifndef IPARSER_H
#define IPARSER_H
#include <qstring.h>
#include "model/GraphData.h"
class IParser {
public:
    virtual ~IParser() = default;

    virtual QString getSourcePath() const = 0;
    virtual void setSourcePath(const QString& filePath) = 0;
    virtual bool parse() = 0;
    virtual QList<GraphData> getData() const = 0;
};
#endif // IPARSER_H
