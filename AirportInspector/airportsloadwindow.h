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

private:
    Ui::AirportsLoadWindow *ui;
};

#endif // AIRPORTSLOADWINDOW_H
