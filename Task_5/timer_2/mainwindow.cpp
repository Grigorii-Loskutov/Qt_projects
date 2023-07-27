#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), lapCount(0) {
    ui->setupUi(this);
    ui->pb_Start_Stop->setCheckable(true);
    connect(ui->pb_Start_Stop, &QPushButton::toggled, this, &MainWindow::onStartStopClicked);
    connect(ui->pb_Clear, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->pb_Lap, &QPushButton::clicked, this, &MainWindow::onLapClicked);
    connect(&stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateTime);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onStartStopClicked() {
    ui->ql_Time->setAlignment(Qt::AlignCenter);
    if (stopwatch.isRunning()) {
        ui->pb_Start_Stop->setText("Start");
        stopwatch.stop();
    } else {
        ui->pb_Start_Stop->setText("Stop");
        stopwatch.start();
    }
    ui->pb_Lap->setEnabled(stopwatch.isRunning());
}

void MainWindow::onResetClicked() {
    ui->pb_Start_Stop->setText("Start");
    ui->ql_Time->setText("00:00:00");
    ui->tb_LapsTime->clear();
    lapCount = 0;
    stopwatch.reset();
    stopwatch.start();

    //ui->pb_Lap->setEnabled(false);
}

void MainWindow::onLapClicked() {
//    int currentTime = stopwatch.getTime();
//    int previousTime = lapCount == 0 ? 0 : stopwatch.getLapTime();
//    int lapTime = currentTime - previousTime;
    int lapTime = stopwatch.getLapTime();
    lapCount++;
    int milliseconds = lapTime % 100;
    int seconds = (lapTime / 1000);
    QString lapText = QString("Круг %1, время: %2.%3 сек")
                          .arg(lapCount)
                          .arg(seconds)
                          .arg(milliseconds);
    ui->tb_LapsTime->append(lapText);
}

void MainWindow::updateTime(int time) {
    int milliseconds = time % 100;
    int seconds = (time / 1000) % 60;
    int minutes = (time / 60000) % 60;
    QString timeString = QString("%1:%2:%3")
                             .arg(minutes, 2, 10, QLatin1Char('0'))
                             .arg(seconds, 2, 10, QLatin1Char('0'))
                             .arg(milliseconds, 2, 10, QLatin1Char('0'));
    ui->ql_Time->setText(timeString);
}
