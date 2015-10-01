/*
 * @copyright  Copyright (c) 2007 Pavel Kral
 * @link       http://x-design.wz.cz/
 * @category   C++
 *
 * For the full copyright and license information, please view
 * the file license.txt that was distributed with this source code.
 */


#include <QtGui>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QHeaderView>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include "customermodel.h"
#include "mainwindow.h"
#include "adddialog.h"
#include "groupmodel.h"

MainWindow::MainWindow()
{
    ui.setupUi ( this );
    setWindowTitle ( tr ( "Contacts" ) );
    setWindowIcon ( QIcon ( ":/icons/icon.png" ) );

    const int rowsize = 150;
    //const int size = 160;

    openConnection();

    searchLabel = new QLabel;
    searchEdit = new QLineEdit;
    //searchEdit->setFixedWidth(size);
    searchLabel->setText ( tr ( "Search contact:" ) );

    ui.toolBar->addWidget ( searchLabel );
    ui.toolBar->addWidget ( searchEdit );
    ui.toolBar->addAction ( ui.actionSearch );
    ui.toolBar->setLayoutDirection ( Qt::LeftToRight );
    //ui.toolBar->addSeparator();

    model2 = new GroupModel ( this );
    model2->setQuery ( "SELECT * FROM groups ORDER BY name ASC" );

    ui.treeGroup->setIconSize ( QSize ( 32,32 ) );
    ui.treeGroup->setModel ( model2 );
    ui.treeGroup->addAction ( ui.actionDelete_group );

    QSqlQuery queryg ( "SELECT * FROM groups ORDER BY name ASC LIMIT 1" );
    queryg.next();
    QString groupstart = queryg.record().value ( "id" ).toString();

    model = new CustomerModel ( this );
    model->setQuery ( "SELECT * FROM contacts WHERE idgroup = "+ groupstart +"" );

    ui.treeView->header()->setDefaultSectionSize ( rowsize );
    ui.treeView->header()->hide();
    ui.treeView->setModel ( model );
    ui.treeView->addAction ( ui.actionRem );
    ui.treeView->hideColumn ( 3 );
    ui.treeView->hideColumn ( 4 );
    ui.treeView->hideColumn ( 5 );
    ui.treeView->hideColumn ( 6 );


}

MainWindow::~ MainWindow()
{
	closeConnection();
}


void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::information ( this, "info","Created by <a href=x-design.wz.cz>www.xdesign.wz.cz</a> GPL licensed." );

}
void MainWindow::on_actionExit_triggered()
{
	QApplication::quit();

}

//#define USE_MYSQL
#ifndef USE_MYSQL
#include "conect.h"
#endif


QSqlDatabase MainWindow::openConnection()
{
	QSqlDatabase db = QSqlDatabase::database();
	if ( !db.isValid() )
	{
#ifndef USE_MYSQL
		createConnection();
		db = QSqlDatabase::database();
#else
		db = QSqlDatabase::database();
		if ( !db.isValid() ) db = QSqlDatabase::addDatabase ( "QSQLITE" );
		if ( !db.isValid() ) throw "database driver error";
		if ( !db.isOpen() )
		{
			//db.setHostName("localhost");
			//db.setUserName("root");
			db.setDatabaseName ( ":contacts:" );
			if ( !db.open() )
			{
				throw "database open error";
			}
		}
#endif
	}
	return db;
}

void MainWindow::closeConnection()
{
	QSqlDatabase db = QSqlDatabase::database();
	if ( db.isOpen() ) db.close();
}

void MainWindow::on_actionAdd_triggered()
{

    QModelIndex ixgroupst = ui.treeGroup->currentIndex();
    if ( ixgroupst.isValid() ){


        int rowst = ixgroupst.row();
        QSqlRecord recordst = model2->record ( rowst );

        QString idgrload = recordst.value ( "id" ).toString();
        QString title = ( "New" );

        AddDialog dlg1 ( title,idgrload,this );
        //dlg1.exec();


        if ( dlg1.exec() == QDialog::Accepted )
        {

                model->setQuery ( "SELECT * FROM contacts WHERE idgroup = "+ dlg1.group +"" );
                ui.treeView->hideColumn ( 3 );
                ui.treeView->hideColumn ( 4 );
                ui.treeView->hideColumn ( 5 );
                ui.treeView->hideColumn ( 6 );
        }
    }
    else{

     QMessageBox::information ( this, "info"," You must create a group first." );

    }


}
void MainWindow::on_treeGroup_clicked()
{
    //QMessageBox::information(this, "info"," datasaved");

    QModelIndex ixgroup = ui.treeGroup->currentIndex();
    int rowg = ixgroup.row();
    QSqlRecord record2 = model2->record ( rowg );
    QString idgroup = record2.value ( "id" ).toString();
    model->setQuery ( "SELECT * FROM contacts WHERE idgroup = "+ idgroup +"" );

}
void MainWindow::on_actionRem_triggered()
{
    QModelIndex ixcustm = ui.treeView->currentIndex();
    if ( ixcustm.isValid() )
    {


        int row = ixcustm.row();
        QSqlRecord record1 = model->record ( row );

        QString idcustm = record1.value ( "id" ).toString();
        QString idgr = record1.value ( "idgroup" ).toString();

        QMessageBox::StandardButton deletecust;
        deletecust =  QMessageBox::warning ( this, tr ( "Delete contact" ),
                                             QString ( tr ( "Are you sure " \
                                                            "do you want to really delete this contact. " ) )
                                             ,
                                             QMessageBox::Yes | QMessageBox::No );


        if ( deletecust == QMessageBox::Yes )
        {
              QSqlQuery query ( "DELETE  FROM contacts WHERE id = "+ idcustm +"" );
              model->setQuery ( "SELECT * FROM contacts WHERE idgroup = "+ idgr +"" );

        }

        else
        {


        }
    }
    else{

    QMessageBox::warning ( this, "info"," You must select the contact" )	;

    }

    //qDebug() << "deleting row:" << row << ok;
}
void MainWindow::on_actionAdd_Group_triggered()
{


    QString table_name = "New";
    bool ok;
    table_name = QInputDialog::getText ( this, tr ( "New group" ),
                                         tr ( "Enter the group name:" ), QLineEdit::Normal,
                                         table_name, &ok );
    if ( ok && !table_name.isEmpty() )
    {

        QSqlQuery queryingroup ( "insert into groups (name) values('"+ table_name +"')" );

        model2->setQuery ( "SELECT * FROM groups ORDER BY name ASC" );
    }
    else
    {
        // QMessageBox::information(this, "info"," You must entrer group name");
    }


}
void MainWindow::on_actionDelete_group_triggered()
{
    QModelIndex ixgrc = ui.treeGroup->currentIndex();

    if ( ixgrc.isValid() )
    {


        int rowgr = ixgrc.row();
        QSqlRecord record2 = model2->record ( rowgr );

        QString idgrr = record2.value ( "id" ).toString();

        QMessageBox::StandardButton deletecust;

        deletecust = QMessageBox::warning ( this, tr ( "Delete group" ),
                                            QString ( tr ( "Are you sure " \
                                                           "do you want to really delete this group." ) )
                                            ,
                                            QMessageBox::Yes | QMessageBox::No );


        if ( deletecust == QMessageBox::Yes )
        {

                QSqlQuery queryGR ( "DELETE  FROM contacts WHERE idgroup = "+ idgrr +"" );
                model->setQuery ( "SELECT * FROM contacts WHERE idgroup = "+ idgrr +"" );
                QSqlQuery query1GR ( "DELETE  FROM groups WHERE id = "+ idgrr +"" );
                model2->setQuery ( "SELECT * FROM groups ORDER BY name ASC" );
        }

        else
        {
        }

    }
    else
    {

        QMessageBox::warning ( this, "info"," You must select the group" );

    }
}
void MainWindow::on_treeView_doubleClicked()
{
    //QMessageBox::information(this, "info"," datasaved")	;

    QModelIndex ixcont = ui.treeView->currentIndex();
    int rowcont = ixcont.row();
    QSqlRecord recordcont = model->record ( rowcont );
    QString idcont = recordcont.value ( "id" ).toString();
    QSqlQuery query ( "SELECT * FROM contacts WHERE id = "+ idcont +"" );
    query.next();
    QString name = query.record().value ( "name" ).toString();
    QString phone = query.record().value ( "phone" ).toString();
    QString mail = query.record().value ( "mail" ).toString();
    QString adress = query.record().value ( "adress" ).toString();
    QString notes = query.record().value ( "notes" ).toString();
    QString id = query.record().value ( "id" ).toString();
    QString idgrload = query.record().value ( "idgroup" ).toString();
    QString title = ( "Contact" );

    AddDialog dlg2 ( title,idgrload,this );

    dlg2.id = id;

    dlg2.lineEdname->setText ( name );
    dlg2.lineEdmail->setText ( mail );
    dlg2.lineEdph->setText ( phone );
    dlg2.textNotes->setText ( notes );
    dlg2.textAdress->setText ( adress );


    if ( dlg2.exec() == QDialog::Accepted ){

        model->setQuery ( "SELECT * FROM contacts WHERE idgroup = "+ dlg2.group +"" );

        ui.treeView->hideColumn ( 3 );
        ui.treeView->hideColumn ( 4 );
        ui.treeView->hideColumn ( 5 );
        ui.treeView->hideColumn ( 6 );


    }
    else
    {

    }

}
void MainWindow::on_actionSearch_triggered()
{

    QString stsearch = searchEdit->text();
    if ( stsearch == 0 ){
        QMessageBox::information ( this, "info","You must enter text." );
    }

    else{
        model->setQuery ( "SELECT name,phone,mail,adress,notes,idgroup,id FROM contacts WHERE name LIKE '"+ stsearch +"%'" );
    }

}

