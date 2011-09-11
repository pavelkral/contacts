/*
 * @copyright  Copyright (c) 2007 Pavel Kral
 * @link       http://x-design.wz.cz/
 * @category   C++
 *
 * For the full copyright and license information, please view
 * the file license.txt that was distributed with this source code.
 */


#ifndef MODEL_H
#define MODEL_H

/**

*/


 #include <QSqlQueryModel>
 #include <QFileIconProvider>
 #include <QVector>

class CustomerModel : public QSqlQueryModel
{
     Q_OBJECT

 public:
     
    CustomerModel( QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual ~CustomerModel();
   
};

#endif


