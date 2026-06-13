#include "maincontroller.h"

MainController::MainController(QObject* parent): QObject(parent)
{
}

void MainController::setChartCreator(IChartCreator* creator)
{
    _chartCreator = creator;
}
void MainController::setView(IChartView* view)
{
    _view = view;
}

void MainController::setDataModel(DataModel* model)
{
    _model = model;

    if(_model)
    {
        connect(_model,&DataModel::dataChanged,this,&MainController::onDataChanged);
    }
}

void MainController::onDataChanged()
{
    if(!_view ||!_model ||!_chartCreator)
    {
        return;
    }

    auto chart =_chartCreator->create(_model->getData());
    _view->displayChart(chart);
}
