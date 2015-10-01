/*
 * @copyright  Copyright (c) 2007 Pavel Kral
 * @link       http://x-design.wz.cz/
 * @category   C++
 *
 * For the full copyright and license information, please view
 * the file license.txt that was distributed with this source code.
 */


#ifndef GROUPMODEL_H
#define GROUPMODEL_H

/**
        @author
*/
#include <QSqlQueryModel>
//#include <QFileIconProvider>
#include <QVector>

class GroupModel : public QSqlQueryModel
{
    Q_OBJECT

    public:

    GroupModel ( QObject *parent = 0 );
    QVariant data ( const QModelIndex &index, int role ) const;
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual ~GroupModel();

};

#endif
