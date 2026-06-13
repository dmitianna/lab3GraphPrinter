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
    connect(
        _chartTypeCombo,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &MainWindow::chartTypeChanged
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

