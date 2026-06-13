#include <QApplication>
#include "mainwindow.h"
#include "mainwindow.h"
#include "maincontroller.h"
#include "model/DataModel.h"
#include "parser/sqliteparser.h"
#include "parser/DateExtracter.h"
#include "charts/LineChartCreator.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    DataModel model;
    LineChartCreator creator;
    MainController controller;

    controller.setView(&window);
    controller.setDataModel(&model);
    controller.setChartCreator(&creator);

    auto extracter =std::make_shared<DateExtracter>();

    SQLiteParser parser("C:/Users/dmiti/Documents/repositories/lab3GraphPrinter/InputData/BLOOD_SUGAR.sqlite",extracter);

    if(!parser.parse())
    {
        return -1;
    }
    model.setData(parser.getData());
    window.show();
    return a.exec();
}
