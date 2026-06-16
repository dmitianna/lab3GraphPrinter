#include "maincontroller.h"
#include "ioc/DIConfiguration.h"
#include "charts/IChartCreator.h"
#include <QFileInfo>
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
    if(!_parser || !_model || !_view)
    {
        return;
    }
    _parser->setSourcePath(filePath);
    QFileInfo info(filePath);
    if(info.suffix().toLower() != "sqlite")
    {
        _view->showError(ControllerMessages::UnsupportedFormat);
        return;
    }
    if(!_parser->parse())
    {
        if(_view)
        {
            _view->cleanChart();
            _view->showError(_parser->getLastError());
        }
        return;
    }

    auto data = _parser->getData();

    if(data.isEmpty())
    {
        if(_view)
        {
            _view->cleanChart();
            _view->showError(ControllerMessages::EmptyData);
        }
        return;
    }

    _model->setData(_parser->getData());
    if(_view)
    {
        _view->showStatus(QString("Загружен файл: %1").arg(QFileInfo(filePath).fileName()));
    }
    _view->setChartControlsEnabled(true);
}

void MainController::onChartTypeChanged(int index)
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
