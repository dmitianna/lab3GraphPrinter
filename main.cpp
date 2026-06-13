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
    SQLiteParser parser("",extracter);

    controller.setView(&window);
    controller.setDataModel(&model);
    controller.setChartCreator(&creator);
    controller.setParser(&parser);

    QObject::connect(&window,&MainWindow::fileSelected,&controller,&MainController::onFileSelected);

    window.show();
    return a.exec();
}
