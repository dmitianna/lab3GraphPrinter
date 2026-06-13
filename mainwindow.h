#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCharts/QChartView>
#include "charts/IChartView.h"

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow, public IChartView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

    void displayChart(QChart* chart) override;
    void cleanChart() override;
    void showError(const QString& message) override;
    void showStatus(const QString& message) override;
private:
    QChartView* _chartView;
};
#endif // MAINWINDOW_H
