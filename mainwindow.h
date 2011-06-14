#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QSqlDatabase>
 #include <QLabel>
class  QSqlQueryModel;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	private:
		Ui::MainWindow ui;
		
	public:
                QLabel *searchLabel;
                QLineEdit *searchEdit;
                QSqlQueryModel *model;
		QSqlQueryModel *model2;
                MainWindow();
		virtual ~MainWindow();
	protected:
		QSqlDatabase openConnection();
		void closeConnection();
	private slots:

		void on_actionExit_triggered();
		void on_actionAbout_triggered();
                void on_actionAdd_triggered();
		void on_actionRem_triggered();
	        void on_treeGroup_clicked();
                void on_actionAdd_Group_triggered();
                void on_actionDelete_group_triggered();
                void on_actionSearch_triggered();
                void on_treeView_doubleClicked ();
private:
};

#endif

