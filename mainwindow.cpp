#include "mainwindow.h"
#include <QMessageBox>
#include <QStatusBar>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    _chartView = new QChartView(this);
    setCentralWidget(_chartView);
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

