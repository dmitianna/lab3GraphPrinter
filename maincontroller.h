#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include "charts/IChartView.h"
#include "model/DataModel.h"
#include "charts/IChartCreator.h"
class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(QObject* parent = nullptr);

    void setView(IChartView* view);
    void setDataModel(DataModel* model);
    void setChartCreator(IChartCreator* creator);

public slots:
    void onDataChanged();

private:
    IChartView* _view = nullptr;
    DataModel* _model = nullptr;
    IChartCreator* _chartCreator = nullptr;
};
#endif // MAINCONTROLLER_H
