#ifndef SQLITEPARSER_H
#define SQLITEPARSER_H
#include "IParser.h"
#include "IDataExtracter.h"
class SQLiteParser: public IParser
{
public:
    SQLiteParser(const QString& sourcePath = "",const IDataExtracter* extracter = nullptr);

private:
    QString _sourcePath;
    QList<GraphData> _data;
    const IDataExtracter* _extracter;
};

#endif // SQLITEPARSER_H
