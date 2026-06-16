#ifndef SQLITEPARSER_H
#define SQLITEPARSER_H
#include "IParser.h"
#include "IDataExtracter.h"
#include <QtSql>
namespace ParserMessages
{
const QString NoExtractor ="Не настроен извлекатель данных";

const QString NoTables ="В базе данных отсутствуют таблицы";

const QString NoValidRecords ="Не найдено ни одной корректной записи";
}

class SQLiteParser: public IParser
{
public:
    SQLiteParser(const QString& sourcePath, std::shared_ptr<IDataExtracter<QDateTime>> extracter);
    QString getSourcePath() const override;
    void setSourcePath(const QString& filePath) override;
    bool parse() override;
    QList<GraphData> getData() const override;
    QString getLastError() const override;
private:
    QString _sourcePath;
    QList<GraphData> _data;
    std::shared_ptr<IDataExtracter<QDateTime>> _extracter ;
    QString _lastError;
};

#endif // SQLITEPARSER_H
