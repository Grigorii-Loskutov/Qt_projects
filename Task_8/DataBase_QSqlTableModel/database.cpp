#include "database.h"
#include "qsqlerror.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    simpleQuery = new QSqlQuery();
    tableWidget = new QTableWidget();


}

DataBase::~DataBase()
{
    delete dataBase;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());


    ///Тут должен быть код ДЗ


    bool status;
    status = dataBase->open();
    if (status){
        tableModel = new QSqlTableModel(this, *dataBase);
    }
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QTableView* tb_result, const requestType filtr)
{

    ///Тут должен быть код ДЗ
    tableModel->setTable("film");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);


//    for (int col = 0; col < tableModel->columnCount(); ++col) {
//        if (col != 1 && col != 2) { // Скрыть все столбцы, кроме второго и третьего
//            tableModel->setColumnHidden(col, true);
//        }
//    }
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Название"));
    tableModel->setHeaderData(2, Qt::Horizontal, tr("Описание"));
    if (filtr == requestAllFilms) {

        tableModel->select();
        tb_result->setModel(tableModel);
        for (int col = 0; col < tableModel->columnCount(); ++col) {
            if (col != 1 && col != 2) { // Скрыть все столбцы, кроме второго и третьего
                tb_result->setColumnHidden(col, true);
            }
        }
        tb_result->resizeColumnsToContents();
        qDebug() << "Request has been sended";
        qDebug() << "DataBase: " << tableModel->database();
        qDebug() << "Table: " << tableModel->tableName();
    }
    else {
        QString request = "SELECT title, description FROM film f "
                                      "JOIN film_category fc on f.film_id = fc.film_id "
                                      "JOIN category c on c.category_id = fc.category_id ";

        if  (filtr == requestComedy) {
            request = request + " WHERE c.name = 'Comedy'";
        }
        else {
            request = request + " WHERE c.name = 'Horror'";
        }
        *simpleQuery = QSqlQuery(*dataBase);
         QSqlError err;
         if(simpleQuery->exec(request) == false){
                err = simpleQuery->lastError();
            }

         emit sig_SendStatusRequest(err);
         qDebug() << "Status error has been emited";
    }
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
void DataBase::ReadAnswerFromDB(int requestType)
{

    tableWidget->setColumnCount(2);
    tableWidget->setRowCount(0);
    QStringList hdrs;
    hdrs << "Название фильма" << "Описание фильма";
    tableWidget->setHorizontalHeaderLabels(hdrs);

    uint32_t conterRows = 0;

    while(simpleQuery->next()){
        QString str;
        tableWidget->insertRow(conterRows);

        for(int i = 0; i<tableWidget->columnCount(); ++i){

            str = simpleQuery->value(i).toString();
            QTableWidgetItem *item = new QTableWidgetItem(str);
            tableWidget->setItem(tableWidget->rowCount() - 1, i, item);
            qDebug() << item;

        }
        ++conterRows;
    }

    emit sig_SendDataFromDB(tableWidget, requestAllFilms);
    qDebug() << "SendDataFromDB has been emited";
}
