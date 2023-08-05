#include "database.h"
#include <QDebug>
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
    status = dataBase->open( );
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
void DataBase::RequestToDB(QString request)
{

    ///Тут должен быть код ДЗ
    qDebug() << "Trying request...";

    *simpleQuery = QSqlQuery(*dataBase);
    QSqlError err;
    if(simpleQuery->exec(request) == false){
           err = simpleQuery->lastError();
       }

    emit sig_SendStatusRequest(err);
    qDebug() << "Status error has been emited";


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
    switch (requestType) {
    case requestAllFilms:
    case requestComedy:
    case requestHorrors:
    {

        tableWidget->setColumnCount(3);
        tableWidget->setRowCount(0);
        QStringList hdrs;
        hdrs << "Название" << "Год выпуска" << "Жанр";
        tableWidget->setHorizontalHeaderLabels(hdrs);

        uint32_t conterRows = 0;

        while(simpleQuery->next()){
            QString str;
            tableWidget->insertRow(conterRows);

            for(int i = 0; i<tableWidget->columnCount(); ++i){

                str = simpleQuery->value(i).toString();
                QTableWidgetItem *item = new QTableWidgetItem(str);
                tableWidget->setItem(tableWidget->rowCount() - 1, i, item);

            }
            ++conterRows;
        }

        emit sig_SendDataFromDB(tableWidget, requestAllFilms);

        break;
    }

    default:
        break;
    }

}
