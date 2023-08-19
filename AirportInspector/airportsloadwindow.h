#ifndef AIRPORTSLOADWINDOW_H
#define AIRPORTSLOADWINDOW_H

#include <QWidget>

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

private:
    Ui::AirportsLoadWindow *ui;

protected:
    void closeEvent(QCloseEvent *event) override;
};




#endif // AIRPORTSLOADWINDOW_H
