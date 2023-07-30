#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QWidget *PlotWidget = new QWidget;
//    PlotWidget->setWindowTitle("SuperPlot");
//    PlotWidget->show();
    return a.exec();
}
