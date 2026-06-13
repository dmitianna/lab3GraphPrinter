#ifndef SQLITEPARSER_H
#define SQLITEPARSER_H
#include "IParser.h"
#include "IDataExtracter.h"
#include <QtSql>
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
