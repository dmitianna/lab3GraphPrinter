#include "maincontroller.h"
#include "ioc/DIConfiguration.h"
#include "charts/IChartCreator.h"
MainController::MainController(QObject* parent): QObject(parent)
{
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
    if(!_view ||!_model)
    {
        return;
    }
    auto chartCreator = gContainer.GetObject<IChartCreator>();
    auto chart = chartCreator->create(_model->getData());
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

void MainController::onChartTypeChanged(
    int index)
{
    if(index == 0)
    {
        DIConfiguration::switchToLineChart();
    }
    else
    {
        DIConfiguration::switchToAreaChart();
    }

    onDataChanged();
}
void MainController::onBlackWhiteChanged(bool enabled)
{
    DIConfiguration::setBlackWhite(enabled);
    onDataChanged();
}
