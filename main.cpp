#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "parser/sqliteparser.h"
#include "parser/DateExtracter.h"
#include <QtCharts/QChartView>
#include "parser/sqliteparser.h"
#include "parser/DateExtracter.h"
#include "charts/LineChartCreator.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    auto extracter = std::make_shared<DateExtracter>();

    SQLiteParser parser("C:/Users/dmiti/Documents/repositories/lab3GraphPrinter/InputData/BLOOD_SUGAR.sqlite",extracter);

    if(!parser.parse()) { return -1; }
    LineChartCreator creator;
    QChart* chart = creator.create( parser.getData() );
    auto* chartView = new QChartView(chart);
    chartView->resize(1200, 700);
    chartView->show();
    return a.exec();
}
