#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("hospital");
    db.setUserName("root");
    db.setPassword("zapanaromero64");


    if (!db.open()) {
        QMessageBox::critical(nullptr, "Error", "No se pudo conectar a la base de datos.");
        qDebug() << "No se pudo conectar a la base de datos:" << db.lastError().text();
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
