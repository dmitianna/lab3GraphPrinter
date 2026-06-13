#include "mainwindow.h"
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    _model = new QFileSystemModel(this);

    _model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    _model->setNameFilters({"*.sqlite"});
    _model->setNameFilterDisables(false);

    _tableView = new QTableView(this);
    _tableView->setModel(_model);
    QString homePath =QDir::homePath();

    _tableView->setRootIndex(_model->setRootPath(homePath));
    _chartView = new QChartView(this);
    splitter->addWidget(_tableView);
    splitter->addWidget(_chartView);

    setCentralWidget(splitter);
    QItemSelectionModel* selectionModel = _tableView->selectionModel();
    connect(
        selectionModel,
        &QItemSelectionModel::selectionChanged,
        this,
        [this](const QItemSelection& selected)
        {
            QModelIndexList indexes =selected.indexes();

            if(indexes.isEmpty())
            {
                return;
            }

            QString filePath =_model->filePath(indexes.first());
            emit fileSelected(filePath);
        }
        );
    resize(1200, 700);
}

void MainWindow::displayChart(QChart* chart)
{
    _chartView->setChart(chart);
}

void MainWindow::cleanChart()
{
    _chartView->setChart(nullptr);
}

void MainWindow::showError(const QString& message)
{
    QMessageBox::critical(this,"Ошибка",message);
}

void MainWindow::showStatus(const QString& message)
{
    statusBar()->showMessage(message);
}

