#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "signals.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void RcvStart();
    void RcvStop();
    void RcvClear();
    void RcvLapTime(QString lap_time);
    void RcvTimeFromTimer();
private slots:
    void on_pb_Start_Stop_toggled(bool checked);

    void on_pb_Lap_clicked();

    void on_pb_Clear_clicked();

private:
    Ui::MainWindow *ui;
    Signals *sig;
};
#endif // MAINWINDOW_H
