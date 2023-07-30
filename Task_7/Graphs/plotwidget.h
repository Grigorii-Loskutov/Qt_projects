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

private:
    Ui::PlotWidget *ui;
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
};

#endif // PLOTWIDGET_H
