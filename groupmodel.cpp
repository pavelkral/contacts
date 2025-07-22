
#include "groupmodel.h"

#include <QIcon>
#include <QPixmap>

GroupModel::GroupModel ( QObject *parent ) :QSqlQueryModel ( parent ){
}

GroupModel::~GroupModel(){
}

QVariant GroupModel::data ( const QModelIndex &index, int role ) const
{
    QVariant ret;
    static QIcon servs ( QPixmap ( ":/icons/Book.png" ) );

    //Model *it = qobject_cast<Model*>(o);
    if ( !index.isValid() )
            return QVariant();
    if ( role == Qt::DisplayRole )
    // Node *item = static_cast<Node*>(index.internalPointer());
    return QSqlQueryModel::data ( index, role );
    //return    ret = index->data(index.column());
    //return   QString::number(index.row()) + ":" + QString::number(index.column());
    if ( role == Qt::DecorationRole )
    {
            if ( index.column() == 0 )
                    return QVariant::fromValue( servs );
    }


    return  QSqlQueryModel::QSqlQueryModel::data ( index, role );

}

