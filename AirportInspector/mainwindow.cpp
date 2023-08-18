#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    //ui->pb_request_shedule->setEnabled(false);

    dataBase = new DataBase(this);
    msg = new QMessageBox(this);
    db_answer = new  QSqlQueryModel(this);
    proxyModel  = new  QSortFilterProxyModel(this);
    QDate CurrentDate {2017, 1, 1};
    ui->dt_dateEnter->setDate(CurrentDate);
    ui->rb_arrival->setChecked(true);
    ui->rb_departure->setChecked(false);
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);

    //Подключение в конструкторе
    if(ui->lb_statusConnect->text() == "Отключено"){

       ui->lb_statusConnect->setText("Подключение");
       ui->lb_statusConnect->setStyleSheet("color : black");


       auto conn = [&]{dataBase->ConnectToDataBase(dataForConnect);};
       QtConcurrent::run(conn);

    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        //ui->pb_request_shedule->setEnabled(false);
    }
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReceiveStatusConnectionToDB(bool status)
{
    if(status){
        ui->act_connect->setText("Отключиться");
        ui->lb_statusConnect->setText("Подключено к БД");
        ui->lb_statusConnect->setStyleSheet("color:green");
        db_answer = dataBase->RequestToDB(AirpotsList_req);
        proxyModel->setSourceModel(db_answer);
        ui->rb_arrival->update();
        ui->rb_departure->update();
        // Устанавливаем сортировку по определенному столбцу (например, столбец с индексом 1) по возрастанию
        proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive); // Настройка чувствительности к регистру
        proxyModel->setSortRole(Qt::DisplayRole); // Роль данных для сортировки
        proxyModel->sort(0, Qt::AscendingOrder); // Сортировка по столбцу 1 в возрастающем порядке

        //ui->cb_AirportsList->setModel(proxyModel);
        //ui->cb_AirportsList->setModelColumn(0);
        //ui->pb_request_shedule->setEnabled(true);
        int rowCount = db_answer->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex codeIndex = db_answer->index(row, 0); // Индекс столбца с кодом аэропорта
            QModelIndex nameIndex = db_answer->index(row, 1); // Индекс столбца с названием аэропорта

            QString airportCode = db_answer->data(codeIndex).toString();
            QString airportName = db_answer->data(nameIndex).toString();

            airportMap.insert(airportCode, airportName);
        }
        for (const QString &airportName : airportMap.keys()) {
            ui->cb_AirportsList->addItem(airportName);
        }
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        ui->lb_statusConnect->setText("Отключено");
        ui->lb_statusConnect->setStyleSheet("color:red");
        msg->exec();
        ui->cb_AirportsList->setModel(nullptr);
    }

}


void MainWindow::on_pb_request_AirportsLis_clicked()
{


}


void MainWindow::on_pb_requestStats_clicked()
{
    QString keyToSearch = ui->cb_AirportsList->currentText();
    if (airportMap.contains(keyToSearch)) {
        QString airportName = airportMap.value(keyToSearch);
        //ui->tl_AirportCode->setText(airportName);
        qDebug() << "Airport name for code" << keyToSearch << "is" << airportName;
    } else {
        qDebug() << "Airport code" << keyToSearch << "not found in the map.";
    }
}


void MainWindow::on_dt_dateEnter_userDateChanged(const QDate &date)
{
    CurrentDate = ui->dt_dateEnter->date();
    if (CurrentDate < minDate){
        CurrentDate = minDate;
        ui->dt_dateEnter->setDate(CurrentDate);
    }
    if (CurrentDate > maxDate){
        CurrentDate = maxDate;
        ui->dt_dateEnter->setDate(CurrentDate);
    }
}


void MainWindow::on_pb_request_shedule_clicked()
{
    QString keyToSearch = ui->cb_AirportsList->currentText();
    QString airportCode = airportMap.value(keyToSearch);
    if (airportMap.contains(keyToSearch)) {
        //ui->tl_AirportCode->setText(airportName);
        qDebug() << "Airport name for code" << keyToSearch << "is" << airportCode;
    } else {
        qDebug() << "Airport code" << keyToSearch << "not found in the map.";
    }
    if (ui->rb_arrival->isChecked() == true){
        request = ArrivalPlains_req + "where f.arrival_airport  = " + "'" +  airportCode + "' "
                "and scheduled_departure::date = date('" + CurrentDate.toString() + "')";
    }
    else if (ui->rb_departure->isChecked() == true){
        request = LivedPlains_req + "where f.departure_airport = " + "'" +  airportCode + "' "
                "and scheduled_departure::date = date('" + CurrentDate.toString() + "')";
    }
    else {
        request = "";
    }

    db_answer = dataBase->RequestToDB(request);
    if (ui->rb_arrival->isChecked() == true){
        db_answer->setHeaderData(0, Qt::Horizontal, tr("Номер рейса"));
        db_answer->setHeaderData(1, Qt::Horizontal, tr("Время вылета"));
        db_answer->setHeaderData(2, Qt::Horizontal, tr("Аэропорт отправления"));
    }
    else {
        db_answer->setHeaderData(0, Qt::Horizontal, tr("Номер рейса"));
        db_answer->setHeaderData(1, Qt::Horizontal, tr("Время вылета"));
        db_answer->setHeaderData(2, Qt::Horizontal, tr("Аэропорт назначения"));

    }
    ui->tv_AirPortsTable->setModel(db_answer);
    for (int row; row < db_answer->rowCount(); ++row){
        QModelIndex cellIndex = db_answer->index(row, 1);
        qDebug() << "Cell Index: " << cellIndex;
        QVariant cellData = db_answer->data(cellIndex);
        qDebug() << "Cell data: " << cellData;
        QTime cellTime = cellData.toTime();
        qDebug() << "Cell time: " << cellData.toTime();
        db_answer->setData(cellIndex, cellTime);
        qDebug() << db_answer->data(cellIndex);
    }
    ui->tv_AirPortsTable->setModel(db_answer);
    ui->tv_AirPortsTable->resizeColumnsToContents();

}

