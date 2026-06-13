#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "parser/sqliteparser.h"
#include "parser/DateExtracter.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    auto extracter = std::make_shared<DateExtracter>();

    SQLiteParser parser("C:/Users/dmiti/Documents/repositories/lab3GraphPrinter/InputData/BLOOD_SUGAR.sqlite",extracter);

    if(parser.parse())
    {
        qDebug() << "SUCCESS";

        auto data = parser.getData();

        qDebug() << "Points:" << data.size();
    }
    else
    {
        qDebug() << "FAIL";
    }
    return a.exec();
}
