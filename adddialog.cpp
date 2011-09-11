//
// C++ Interface:
//
// Description:
//
// Author:Pavel Kral (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//

#include <QtGui>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include "adddialog.h"
#include "mainwindow.h"
#include "groupmodel.h"

AddDialog::AddDialog(const QString title,const QString idgrload,QWidget *parent)
        : QDialog(parent)
 
{
   
     setupUi(this);
     setWindowTitle(title);
     //createToolBar();
     QSqlQuery querycombo("SELECT * FROM groups ORDER BY name ASC");
    
     while (querycombo.next()) {
         QString country = querycombo.record().value("name").toString();
         QVariant id_group = querycombo.record().value("id");
         comboBox->addItem(country,id_group);
     }
     
     int idcount = comboBox->count();
     
     int i;

     for(i = 0; i < idcount; i++){
         QString id_groups = comboBox->itemData(i).toString();
             if(id_groups == idgrload){
                 comboBox-> setCurrentIndex (i);
             }
     }
       
          

}


AddDialog::~AddDialog()
{

}
void AddDialog::on_btcancel_clicked()
{
     reject();

}
void AddDialog::on_btsave_clicked()
{
       QString title = windowTitle();
       QString stname = lineEdname->text();
       //stadr.replace(QString("\n"), QString("\n<br>"));
       QString stphone = lineEdph->text();
       QString stmail = lineEdmail ->text();
       QString stadress = textAdress->toPlainText();
       QString stnotes = textNotes->toPlainText();
       QString id_group = comboBox->itemData(comboBox->currentIndex()).toString();

     
       if(title == "New"){

           if(stname == 0){
           QMessageBox::information(this, "info"," You must enter name.");
           }
           else if(stphone == 0){
           QMessageBox::information(this, "info"," You must enter phone.");
            }
           else {
           //int id_gr = comboBox->currentIndex();
           // qDebug() << "index:" << id_gr;
           // qDebug() << "str:" << id_group;

           QSqlQuery query("insert into contacts (name,phone,mail,adress,notes,idgroup) values ('"+ stname +"','"+ stphone +"','"+ stmail +"','"+ stadress +"','"+ stnotes +"','"+id_group +"')");

           group = id_group;

           accept();

         }
    }
    else{
      
     group = id_group;
      //qDebug() << "index:" << id;

     QSqlQuery query("update contacts  set name = '"+ stname +"' WHERE id = '"+ id +"'");
     QSqlQuery query1("update contacts  set mail = '"+ stmail +"' WHERE id = '"+ id +"'");
     QSqlQuery query2("update contacts  set phone = '"+ stphone +"' WHERE id = '"+ id +"'");
     QSqlQuery query3("update contacts  set adress = '"+ stadress +"' WHERE id = '"+ id +"'");
     QSqlQuery query4("update contacts set notes = '"+ stnotes +"' WHERE id = '"+ id +"'");
     QSqlQuery query5("update contacts set idgroup = '"+ id_group +"' WHERE id = '"+ id +"'");
     

     accept();
 
    }

}


