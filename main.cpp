#include <QApplication>
#include "mainwindow.h"
#include "mainwindow.h"
#include "maincontroller.h"
#include "model/DataModel.h"
#include "parser/sqliteparser.h"
#include "parser/DateExtracter.h"
#include "ioc/DIConfiguration.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DIConfiguration::configure();
    MainWindow window;
    DataModel model;
    MainController controller;

    auto extracter =std::make_shared<DateExtracter>();
    SQLiteParser parser("",extracter);

    controller.setView(&window);
    controller.setDataModel(&model);
    controller.setParser(&parser);

    QObject::connect(&window,&MainWindow::fileSelected,&controller,&MainController::onFileSelected);
    QObject::connect(&window,&MainWindow::chartTypeChanged,&controller,&MainController::onChartTypeChanged);
    window.show();
    return a.exec();
}
