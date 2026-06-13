#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include "charts/IChartView.h"
#include "model/DataModel.h"
#include "charts/IChartCreator.h"
#include "parser/IParser.h"
class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(QObject* parent = nullptr);

    void setView(IChartView* view);
    void setDataModel(DataModel* model);
    void setChartCreator(IChartCreator* creator);
    void setParser(IParser* parser);
public slots:
    void onDataChanged();
    void onFileSelected(const QString& filePath);
private:
    IChartView* _view = nullptr;
    DataModel* _model = nullptr;
    IChartCreator* _chartCreator = nullptr;
    IParser* _parser = nullptr;
};
#endif // MAINCONTROLLER_H
