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
void MainController::setParser(IParser* parser)
{
    _parser = parser;
}

void MainController::onFileSelected(const QString& filePath)
{
    if(!_parser || !_model)
    {
        return;
    }

    _parser->setSourcePath(filePath);

    if(!_parser->parse())
    {
        if(_view)
        {
            _view->showError("Не удалось загрузить файл");
        }
        return;
    }

    _model->setData(_parser->getData());
}
