#include "airportsloadwindow.h"
#include "ui_airportsloadwindow.h"

AirportsLoadWindow::AirportsLoadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirportsLoadWindow)
{
    ui->setupUi(this);
    // Создаем макеты для вкладок
    QVBoxLayout *layoutMonth = new QVBoxLayout();
    QVBoxLayout *layoutYear = new QVBoxLayout();

    // Создаем графики и добавляем их в макеты
    QChartView *chartViewMonth = new QChartView();
    layoutMonth->addWidget(chartViewMonth);

    QChartView *chartViewYear = new QChartView();
    layoutYear->addWidget(chartViewYear);

    // Добавляем макеты во вкладки
    ui->tab_month->setLayout(layoutMonth);
    ui->tab_year->setLayout(layoutYear);


}

AirportsLoadWindow::~AirportsLoadWindow()
{
//    delete chart;
//    delete chartView;
    delete ui;
}


void AirportsLoadWindow::on_pb_close_clicked()
{
    close();
}

void  AirportsLoadWindow::closeEvent(QCloseEvent *event)
{
    emit destroyed();
}

void AirportsLoadWindow::ReceiveYearStats(QStandardItemModel* YearStats)
{

}
void AirportsLoadWindow::ReceivePerDayStats(QStandardItemModel* PerDayStats)
{
    NULL;
}
void AirportsLoadWindow::ReceiveAirportName(QString AirportName)
{
    ui->tl_AirportName->setText("Статистика вылетов и прилетов для аэропорта: " + AirportName);
}
