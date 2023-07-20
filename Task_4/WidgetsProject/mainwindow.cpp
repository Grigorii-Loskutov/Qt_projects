#include "mainwindow.h"
#include "./ui_mainwindow.h"
int progress = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioButton->setText("Position_1");
    ui->radioButton_2->setText("Position_2");
    ui->pushButton->setCheckable(1); //сделал кнопку Toggle?
    ui->groupBox->setTitle("Position select");
    for(int iter = 0;iter<10;iter++){
        ui->comboBox->addItem(QString("Case %1").arg(iter));
    }
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10);
    ui->progressBar->setValue(progress);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    if(progress != 10) {
        progress++;
    }
    else {
        progress = 0;
    }
    ui->progressBar->setValue(progress);
}

