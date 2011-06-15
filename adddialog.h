//
// C++ Interface:
//
// Description: 
//
// Author:Pavel Kral (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

/**
        @author Pavel Kral
*/
#include "ui_adddialog.h"

#include <QDialog>
 #include <QToolBar>


class  QSqlQueryModel;

class AddDialog : public QDialog, public Ui::AddDialog 
 {
     Q_OBJECT

 public:
     QString group;
     QString id;
     AddDialog(const QString title,const QString idgrload,QWidget *parent = 0);
     virtual ~AddDialog();

      //QToolBar *fileToolBar;
      //void createToolBar();
 
private slots:
      void on_btsave_clicked();
      void on_btcancel_clicked();
      //void on_tableView_doubleClicked ();
      // void checkValues();
 };


#endif

