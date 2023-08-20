#include "airportsloadwindow.h"
#include "ui_airportsloadwindow.h"
#include <QDebug>
#include <QDateTime>>

AirportsLoadWindow::AirportsLoadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirportsLoadWindow)
{
    ui->setupUi(this);

    chartYear = new QChart();
    seriesYear = new QBarSeries(this);
    chartViewYear = new QChartView(chartYear);
    chartYear->addSeries(seriesYear);
    //chartYear->createDefaultAxes();

    chartMonth = new QChart();
    seriesMonth = new QLineSeries(this);
    chartViewMonth = new QChartView(chartMonth);
    chartMonth->addSeries(seriesMonth);
    //chartMonth->createDefaultAxes();


    // Создаем макеты для вкладок
    QVBoxLayout *layoutMonth = new QVBoxLayout(this);
    QVBoxLayout *layoutYear = new QVBoxLayout(this);

    layoutMonth->addWidget(chartViewMonth);
    layoutMonth->addWidget(ui->cb_monthSelect);
    //ui->cb_monthSelect->show();
    layoutYear->addWidget(chartViewYear);


    // Добавляем макеты во вкладки
    ui->tab_month->setLayout(layoutMonth);
    ui->tab_year->setLayout(layoutYear);

    chartViewYear->show();
    chartViewMonth->show();

    for(int monthIter = 0; monthIter < 12; ++monthIter){
        QString month;
        switch (monthIter) {
        case 0:
            month = "Январь";
            break;
        case 1:
            month = "Февраль";
            break;
        case 2:
            month = "Март";
            break;
        case 3:
            month = "Апрель";
            break;
        case 4:
            month = "Май";
            break;
        case 5:
            month = "Июнь";
            break;
        case 6:
            month = "Июль";
            break;
        case 7:
            month = "Август";
            break;
        case 8:
            month = "Сентябрь";
            break;
        case 9:
            month = "Октябрь";
            break;
        case 10:
            month = "Ноябрь";
            break;
        case 11:
            month = "Декабрь";
            break;
        default:
            break;
        }
        ui->cb_monthSelect->addItem(QString(month).arg(monthIter));
    }



}

AirportsLoadWindow::~AirportsLoadWindow()
{
    delete chartYear;
    delete chartViewYear;
    delete chartMonth;
    delete chartMonth;
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
    seriesYear->clear();
    int rangeY = 0;

    for (int row = 0; row < YearStats->rowCount(); ++row) {

        QModelIndex index_val = YearStats->index(row, 0);
        QModelIndex index_month = YearStats->index(row, 1);

        QVariant data = YearStats->data(index_val);
        int value = data.toInt();
        if (value >rangeY) {
            rangeY = value;
        }

        QVariant QVarDate = YearStats->data(index_month);
        QDateTime dateTime = QVarDate.toDateTime();
        QDate date = dateTime.date();
        int month = date.month();
        int year = date.year();
        QString monthString = QString("%1.%2").arg(month).arg(year);

        QBarSet *set = new QBarSet(monthString);
        *set << value;
        seriesYear->append(set);
        //qDebug() << value;

    }


   axisX_year = new QValueAxis(this);
   axisY_year = new QValueAxis(this);

   axisX_year->setRange(-0.5, 0.5);
   axisX_year->setTitleText("Месяц");
   axisX_year->setLabelFormat("%d"); // Формат отображения меток оси X

   axisY_year->setRange(0, rangeY);
   axisY_year->setTitleText("Количество рейсов");

   chartYear->addAxis(axisX_year, Qt::AlignBottom);
   chartYear->addAxis(axisY_year, Qt::AlignLeft);
   seriesYear->attachAxis(axisX_year);
   seriesYear->attachAxis(axisY_year);
   chartYear->createDefaultAxes();

}
void AirportsLoadWindow::ReceivePerDayStats(QStandardItemModel* PerDayStats)
{
    NULL;
}
void AirportsLoadWindow::ReceiveAirportName(QString AirportName)
{
    ui->tl_AirportName->setText("Статистика вылетов и прилетов для аэропорта: " + AirportName);
}
