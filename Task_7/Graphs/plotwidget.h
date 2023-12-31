#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QtCharts>

namespace Ui {
class PlotWidget ;
}

class PlotWidget  : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWidget(QWidget *parent = nullptr);
    void plotData(const QVector<double>& data);
    ~PlotWidget();

private:
    Ui::PlotWidget *ui;
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
};
#endif // PLOTWIDGET_H
