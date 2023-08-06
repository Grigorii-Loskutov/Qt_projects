#include "database.h"
#include "qsqlerror.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    tableModel = new QSqlTableModel();

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

    tableModel->select();
    tableModel->setHeaderData(2, Qt::Horizontal, tr("Название"));
    tableModel->setHeaderData(3, Qt::Horizontal, tr("Описание"));
    switch (filtr){

    case requestAllFilms:
       tableModel->setFilter("");
       break;
    case requestComedy:
        tableModel->setFilter("c.name = 'Comedy'");
        break;
    case requestHorrors:
        tableModel->setFilter("c.name = 'Horror'");
        break;
    }

    tb_result->setModel(tableModel);
    qDebug() << "Request has been sended";
    qDebug() << "DataBase: " << tableModel->database();
    qDebug() << "Table: " << tableModel->tableName();

}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
