
#ifndef CONECT_H
#define CONECT_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("contacts");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    
    query.exec("create table contacts (name varchar(20), phone varchar(20), mail varchar(40),adress text,notes text,idgroup INTEGER ,id INTEGER primary key autoincrement)");
    query.exec("create table groups (name varchar(25),id INTEGER primary key autoincrement)");
    //query.exec("insert into groups (name)values('Work')");
    //query.exec("insert into contacts (name,phone,mail,idgroup) values ('a','a','a','2')");



   return true;
}

#endif

