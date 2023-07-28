#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtConcurrent>

#include "ExampleRace.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void StartRace( void );


private slots:

    void on_pb_start_clicked();

private:
    Ui::MainWindow *ui;
    uint32_t number = 0, countFinish = 0;

    QMutex m;
    Controller *race1;
    Controller *race2;

    ExampleRace *concurRace1;
    ExampleRace *concurRace2;

    QFuture<void> futRace1;
    QFuture<void> futRace2;
    QFutureWatcher<void> whFutRace1;
    QFutureWatcher<void> whFutRace2;
};


















#endif // MAINWINDOW_H
