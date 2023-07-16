#include "mainwindow.h"
#include "./ui_mainwindow.h"
int iter = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plusButton_clicked()
{
    iter++;
    ui->setValue->setValue(iter);
    ui->lineEdit->setText("Plus");
}


void MainWindow::on_minusButton_clicked()
{
    iter--;
    ui->setValue->setValue(iter);
    ui->lineEdit->setText("Minus");

}


void MainWindow::on_minusButton_2_clicked()
{
    iter=0;
    ui->setValue->setValue(iter);
    ui->lineEdit->setText("Clear");

}

