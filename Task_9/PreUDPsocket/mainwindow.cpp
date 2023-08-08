#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendDataToGUI, this, &MainWindow::DisplayRecieveData);
    /*
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);

    });
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    //timer->start(TIMER_DELAY);
    QByteArray dataToSend;
    QDataStream outStr(&dataToSend, QIODevice::WriteOnly);
    QString strToSend;
    strToSend = ui->te_send->toPlainText();
    outStr << strToSend;

    udpWorker->SendDatagram(dataToSend);
}


void MainWindow::DisplayRecieveData(QString data, QString senderAddr, int size)
{
    /*
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));
    */
    ui->te_result->append("Принято сообщение: "  + data + " от отправителя " + senderAddr + ", размер сообщения (байт): " + QString("%1").arg(size));


}

/*
void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}
*/
