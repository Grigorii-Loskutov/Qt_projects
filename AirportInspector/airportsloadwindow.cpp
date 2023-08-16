#include "airportsloadwindow.h"
#include "ui_airportsloadwindow.h"

AirportsLoadWindow::AirportsLoadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirportsLoadWindow)
{
    ui->setupUi(this);
}

AirportsLoadWindow::~AirportsLoadWindow()
{
    delete ui;
}
