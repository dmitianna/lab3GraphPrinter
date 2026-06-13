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
        qDebug() << date << value;
    }
    _data = parsed;

    db.close();

    return true;
}

QList<GraphData> SQLiteParser::getData() const
{
    return _data;
}
