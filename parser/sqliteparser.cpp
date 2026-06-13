#include "sqliteparser.h"
#include <QtSql>
SQLiteParser::SQLiteParser(const QString& sourcePath, const IDataExtracter<QDateTime>* extracter): _sourcePath(sourcePath),_extracter(extracter) {}
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
    if(!_extracter) return false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(_sourcePath);

    if(!db.open()) return false;

    auto tables = db.tables();

    if(tables.isEmpty()) return false;

    QSqlQuery query;

    if(!query.exec( "SELECT * FROM " + tables.first()))
    {
        return false;
    }

    QList<GraphData> parsed;

    while(query.next())
    {
        //заглушка
    }

    return true;
}

QList<GraphData> SQLiteParser::getData() const
{
    return _data;
}
