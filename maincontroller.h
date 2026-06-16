#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include "charts/IChartView.h"
#include "model/DataModel.h"
#include "parser/IParser.h"

namespace ControllerMessages
{
const QString UnsupportedFormat ="Поддерживаются только файлы SQLite";
const QString EmptyData ="Файл не содержит данных для построения графика";
}
class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(QObject* parent = nullptr);

    void setView(IChartView* view);
    void setDataModel(DataModel* model);
    void setParser(IParser* parser);
public slots:
    void onDataChanged();
    void onFileSelected(const QString& filePath);
    void onChartTypeChanged(int index);
    void onBlackWhiteChanged(bool enabled);
private:
    IChartView* _view = nullptr;
    DataModel* _model = nullptr;
    IParser* _parser = nullptr;
};
#endif // MAINCONTROLLER_H
