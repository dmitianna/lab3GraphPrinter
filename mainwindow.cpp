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
#include <QLabel>
#include <QSizePolicy>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    QToolBar* toolBar =new QToolBar("Main Toolbar", this);
    toolBar->setMovable(false);
    QPushButton* chooseDirectoryButton = new QPushButton("Выбрать путь", this);
    _chartTypeCombo = new QComboBox(this);
    _chartTypeCombo->addItem("Line Chart");
    _chartTypeCombo->addItem("Area Chart");
    QWidget* leftSpacer = new QWidget(this);
    QWidget* rightSpacer = new QWidget(this);
    leftSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    rightSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QLabel* chartLabel = new QLabel("Выберите тип диаграммы ", this);
    addToolBar(toolBar);
    QPushButton* printButton =new QPushButton("Печать графика",this);
    _blackWhiteCheckBox =new QCheckBox("Черно-белый график ", this);
    toolBar->addWidget(chooseDirectoryButton);
    toolBar->addWidget(leftSpacer);
    toolBar->addWidget(chartLabel);
    toolBar->addWidget(_chartTypeCombo);
    toolBar->addSeparator();
    toolBar->addWidget(_blackWhiteCheckBox);
    toolBar->addSeparator();
    toolBar->addWidget(printButton);
    toolBar->addWidget(rightSpacer);
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

    _tableView = new QTableView;
    _tableView->setModel(_model);

    QString homePath = QDir::homePath();
    _model->setRootPath(homePath);
    _tableView->setRootIndex(_model->index(homePath));
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
    showStatus("Выберите файл БД");
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
    _chart = nullptr;
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
        showError(ViewMessages::NoChartForPrint);
        return;
    }

    if(_chart->series().isEmpty())
    {
        showError(ViewMessages::NoChartForPrint);
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
