#include "sqliteparser.h"

SQLiteParser::SQLiteParser(const QString&, const IDataExtracter<QDateTime>*) {}
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
    return 0;
}

QList<GraphData> SQLiteParser::getData() const
{
    return _data;
}
