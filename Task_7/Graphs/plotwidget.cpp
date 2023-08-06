#include "plotwidget.h"
#include <QDebug>
#include <algorithm>

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent)
{
    chart = new QChart();
    series = new QLineSeries(this);
    chartView = new QChartView(chart);
    chart->addSeries(series);

    //chart->createDefaultAxes();  //не подходит

    chart->setTitle("Processed Data");
    //chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    setLayout(layout);
    chartView->show();
}

PlotWidget::~PlotWidget()
{
    delete chart;
    delete chartView;
    //delete axisX;
    //delete axisY;

}

void PlotWidget::plotData(const QVector<double>& data)
{
    series->clear();

    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);

    axisX->setRange(0, data.size()); // Задаем минимальное и максимальное значение для оси X
    chart->addAxis(axisX, Qt::AlignBottom);

    double yMax = *std::max(data.begin(),data.end());
    double yMin = *std::min(data.begin(),data.end());
    axisY->setRange(yMin-0.1, yMax+0.1); // Задаем минимальное и максимальное значение для оси Y
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    for (int i = 0; i < data.size(); ++i)
    {
        series->append(i, data.at(i));
        //qDebug() << "point appended: " << data.at(i);

    }
    chartView->chart()->createDefaultAxes();
}
