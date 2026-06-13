#include "sqliteparser.h"

SQLiteParser::SQLiteParser(const QString&,const IDataExtracter*) {}
QString SQLiteParser::getSourcePath() const
{
    return _sourcePath;
}

void SQLiteParser::setSourcePath(const QString& filePath)
{
    _sourcePath = filePath;
}

bool SQLiteParser::parse()
{
    return false;
}

QList<GraphData> SQLiteParser::getData() const
{
    return _data;
}
