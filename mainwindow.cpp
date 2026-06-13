#include "mainwindow.h"
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    _chartView = new QChartView(this);
    setCentralWidget(_chartView);
    QMenu* fileMenu =menuBar()->addMenu("Файл");
    QAction* openAction =fileMenu->addAction("Открыть");
    connect(openAction,&QAction::triggered,this,
        [this]()
        {
            QString fileName =QFileDialog::getOpenFileName(this,"Выберите SQLite файл",QString(),"*.sqlite");

            if(!fileName.isEmpty())
            {
                emit fileSelected(fileName);
            }
        });
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

