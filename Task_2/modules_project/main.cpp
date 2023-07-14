#include <QCoreApplication>
#include <QUdpSocket>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    QUdpSocket* udpSocket = new QUdpSocket();
     delete udpSocket;
    QSqlDatabase* database = new QSqlDatabase();
     delete database;
    return a.exec();
}
