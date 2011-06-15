//
// C++ Interface:
//
// Description:
//
// Author:Pavel Kral (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef MODEL_H
#define MODEL_H

/**

*/


 #include <QSqlQueryModel>
 #include <QFileIconProvider>
 #include <QVector>

class Model : public QSqlQueryModel
{
     Q_OBJECT

 public:
     
    Model( QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual ~Model();
   
};

#endif


