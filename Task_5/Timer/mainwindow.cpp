#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

unsigned int Lap_number = 0;
bool run = false;
QString time_str = "0";
QString lap_time_str = "";
float time_float = 0;
float time_last_lap = 0;
QTimer *timer = new QTimer();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sig = new Signals(this);
    ui->pb_Start_Stop->setCheckable(true);
    connect(sig, &Signals::set_Start, this, &MainWindow::RcvStart);
    connect(sig, &Signals::set_Stop, this, &MainWindow::RcvStop);
    connect(sig, &Signals::set_LapTime, this, &MainWindow::RcvLapTime);
    connect(sig, &Signals::set_Clear, this, &MainWindow::RcvClear);


    connect(timer, &QTimer::timeout, this,  &MainWindow:: RcvTimeFromTimer);
}

MainWindow::~MainWindow()
{
    delete ui;    
    delete timer;
}

void MainWindow::RcvStart(){
    ui->ql_Time->setAlignment(Qt::AlignCenter);
    //ui->ql_Time->setText("Started");
    timer->start(100);

}

void MainWindow::RcvStop(){
    ui->ql_Time->setAlignment(Qt::AlignCenter);
    //ui->ql_Time->setText("Stoped");
    timer->stop();
    Lap_number = 0;
    time_str = "0";
    lap_time_str = "";
    time_float = 0;
    time_last_lap = 0;

}

void MainWindow::RcvClear(){
    ui->tb_LapsTime->clear();
    Lap_number = 0;
    time_str = "0";
    lap_time_str = "";
    time_float = 0;
    time_last_lap = 0;
}

void MainWindow::RcvTimeFromTimer(){
    time_float += 0.1;
    time_str = QString("%1").arg(time_float);
    ui->ql_Time->setText(time_str);
    //qDebug() << time_float;
}

void MainWindow::RcvLapTime(QString lap_time){
    if (run == true)
    {
        Lap_number++;
        ui->tb_LapsTime->append(QString("Lap %1. Time: ").arg(Lap_number) + lap_time + "sec");
    }
    //qDebug() << Lap_number;
}

void MainWindow::on_pb_Start_Stop_toggled(bool checked)
{
    if(checked) {
        emit sig->set_Start();
        ui->pb_Start_Stop->setText("Stop");
        run = true;
        emit sig->set_Clear();
    }
    else {
        emit sig->set_Stop();
        ui->pb_Start_Stop->setText("Start");
        run = false;
    }
}


void MainWindow::on_pb_Lap_clicked()
{
    //qDebug() << "Lap clicked";
    time_last_lap = time_float - time_last_lap;
    lap_time_str = QString("%1").arg(time_last_lap);
    emit sig->set_LapTime(lap_time_str);
}


void MainWindow::on_pb_Clear_clicked()
{
    emit sig->set_Clear();
}

