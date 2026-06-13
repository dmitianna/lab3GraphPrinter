#include "sqliteparser.h"
#include <QtSql>
#include <memory>
SQLiteParser::SQLiteParser(const QString& sourcePath, std::shared_ptr<IDataExtracter<QDateTime>> extracter): _sourcePath(sourcePath),_extracter(std::move(extracter)) {}
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
    if(!_extracter)
    {
        _lastError = "Не настроен извлекатель данных";
        return false;
    }

    const QString connectionName ="parser_connection";
    QSqlDatabase db;

    if(QSqlDatabase::contains(connectionName))
    {
        db =QSqlDatabase::database(connectionName);
    }
    else
    {
        db =QSqlDatabase::addDatabase("QSQLITE",connectionName);
    }
    db.setDatabaseName(_sourcePath);

    if(!db.open())
    {
        _lastError = db.lastError().text();
        return false;
    }

    auto tables = db.tables();

    if(tables.isEmpty())
    {
        _lastError = "В базе данных отсутствуют таблицы";
        return false;
    }

    QSqlQuery query(db);

    if(!query.exec( "SELECT * FROM " + tables.first()))
    {
        _lastError = query.lastError().text();
        return false;
    }

    QList<GraphData> parsed;

    while(query.next())
    {
        QDateTime date =_extracter->extract(query.value(0).toString());

        if(!date.isValid())
        {
            continue;
        }

        bool ok = false;

        double value = query.value(1).toDouble(&ok);

        if(!ok)
        {
            continue;
        }

        parsed.push_back({date.toMSecsSinceEpoch(),value});
    }
    if(parsed.isEmpty())
    {
        _lastError ="Не найдено ни одной корректной записи";
        return false;
    }
    _data = parsed;
    query.finish();
    db.close();
    return true;
}

QList<GraphData> SQLiteParser::getData() const
{
    return _data;
}
QString SQLiteParser::getLastError() const
{
    return _lastError;
}
