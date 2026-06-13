#include "mainwindow.h"
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QToolBar>
#include <QPushButton>
#include <QDir>
#include <QPdfWriter>
#include <QPainter>
#include <QCheckBox>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    QToolBar* toolBar =new QToolBar("Main Toolbar", this);
    QPushButton* chooseDirectoryButton = new QPushButton("Выбрать путь", this);
    _chartTypeCombo = new QComboBox(this);
    _chartTypeCombo->addItem("Line Chart");
    _chartTypeCombo->addItem("Area Chart");
    addToolBar(toolBar);
    toolBar->addWidget(chooseDirectoryButton);
    toolBar->addSeparator();
    toolBar->addWidget(_chartTypeCombo);
    QPushButton* printButton =new QPushButton("Печать",this);
    toolBar->addSeparator();
    toolBar->addWidget(printButton);
    _blackWhiteCheckBox =new QCheckBox("Ч/Б", this);
    toolBar->addWidget(_blackWhiteCheckBox);
    connect(
        _chartTypeCombo,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &MainWindow::chartTypeChanged
        );
    connect(
        printButton,
        &QPushButton::clicked,
        this,
        &MainWindow::printChart
        );
    connect(
        chooseDirectoryButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            QString dirPath =
                QFileDialog::getExistingDirectory(this,"Выберите папку");

            if(dirPath.isEmpty())
            {
                return;
            }

            _model->setRootPath(dirPath);

            _tableView->setRootIndex(_model->index(dirPath));
        }
        );
    connect(
        _blackWhiteCheckBox,
        &QCheckBox::toggled,
        this,
        &MainWindow::blackWhiteChanged
        );
    _model = new QFileSystemModel(this);

    _model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    _model->setNameFilters({"*.sqlite"});
    _model->setNameFilterDisables(false);

    _tableView = new QTableView;
    _tableView->setModel(_model);
    QString homePath =QDir::homePath();

    _tableView->setRootIndex(_model->setRootPath(homePath));
    _chartView = new QChartView;
    splitter->addWidget(_tableView);
    splitter->addWidget(_chartView);
    QList<int> sizes;
    sizes << 500 << 700;
    splitter->setSizes(sizes);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);
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
    setChartControlsEnabled(false);
}

void MainWindow::displayChart(QChart* chart)
{
    if(!chart)
    {
        return;
    }

    _chartView->setChart(chart);

    _chart = chart;

    showStatus("График обновлен");
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

void MainWindow::printChart()
{
    if(!_chart)
    {
        showError("Нет графика для печати");
        return;
    }

    if(_chart->series().isEmpty())
    {
        showError("Нет графика для печати");
        return;
    }

    QString filePath =QFileDialog::getSaveFileName(this,"Сохранить график","","PDF (*.pdf)");
    if(filePath.isEmpty())
    {
        return;
    }
    QPdfWriter pdfWriter(filePath);
    QPainter painter(&pdfWriter);
    _chartView->render(&painter);
    painter.end();
    showStatus("График сохранён в PDF");
}
void MainWindow::setChartControlsEnabled(bool enabled)
{
    _chartTypeCombo->setEnabled(enabled);
    _blackWhiteCheckBox->setEnabled(enabled);
}
