#ifndef AIRPORTSLOADWINDOW_H
#define AIRPORTSLOADWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QtCharts>

namespace Ui {
class AirportsLoadWindow;
}

class AirportsLoadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AirportsLoadWindow(QWidget *parent = nullptr);
    ~AirportsLoadWindow();

signals:
    //void PlotWindowclosed();
private slots:
    void on_pb_close_clicked();

public slots:
    void ReceiveYearStats(QStandardItemModel* YearStats);
    void ReceivePerDayStats(QStandardItemModel* PerDayStats);
    void ReceiveAirportName(QString AirportName);


private:
    Ui::AirportsLoadWindow *ui;
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

protected:
    void closeEvent(QCloseEvent *event) override;
};


#endif // AIRPORTSLOADWINDOW_H
