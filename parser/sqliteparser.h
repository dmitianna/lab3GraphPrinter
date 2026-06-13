#ifndef SQLITEPARSER_H
#define SQLITEPARSER_H
#include "IParser.h"
#include "IDataExtracter.h"
class SQLiteParser: public IParser
{
public:
    SQLiteParser(const QString& sourcePath = "",const IDataExtracter* extracter = nullptr);
    QString getSourcePath() const override;
    void setSourcePath(const QString& filePath) override;
    bool parse() override;
    QList<GraphData> getData() const override;
private:
    QString _sourcePath;
    QList<GraphData> _data;
    const IDataExtracter* _extracter;
};

#endif // SQLITEPARSER_H
