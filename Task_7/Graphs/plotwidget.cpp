#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent)
{
    chart = new QChart;
    series = new QLineSeries;
    chartView = new QChartView(chart);
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Processed Data");
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    setLayout(layout);
    chartView->show();
}

void PlotWidget::plotData(const QVector<double>& data)
{
    series->clear();
    for (int i = 0; i < data.size(); ++i)
    {
        series->append(i, data.at(i));
    }
}
