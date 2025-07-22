
#include "customermodel.h"
#include <QIcon>
#include <QPixmap>

CustomerModel::CustomerModel(QObject *parent) : QSqlQueryModel(parent) {}

CustomerModel::~CustomerModel() {}

QVariant CustomerModel::data(const QModelIndex &index, int role) const {
    QVariant ret;
    static QIcon services(QPixmap(":/icons/user.png"));
    static QIcon phone(QPixmap(":/icons/phone.png"));
    static QIcon mail(QPixmap(":/icons/03.png"));
    // Model *it = qobject_cast<Model*>(o);
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
        // Node *item = static_cast<Node*>(index.internalPointer());
        return QSqlQueryModel::data(index, role);
    // return    ret = index->data(index.column());
    // return   QString::number(index.row()) + ":" +
    // QString::number(index.column());
    if (role == Qt::DecorationRole) {
        if (index.column() == 0)
            return QVariant::fromValue(services);
    }
    if (role == Qt::DecorationRole) {
        if (index.column() == 1)
            // return QColor(Qt::darkRed);
            // return  QColor( 155 , 155, 155, 255 );
            return QVariant::fromValue(phone);
    }
    if (role == Qt::DecorationRole) {
        if (index.column() == 2)
            // return QColor(Qt::darkRed);
            return QVariant::fromValue(mail);
    }

    if (role == Qt::ForegroundRole) {
        if (index.column() == 1)
            // return QColor(Qt::darkRed);
            return QColor(Qt::black);
    }
    if (role == Qt::ForegroundRole) {
        if (index.column() == 2)
            // return QColor(Qt::darkRed);
            return QColor(Qt::black);
    }
    return QSqlQueryModel::QSqlQueryModel::data(index, role);
}

QVariant CustomerModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
    static QIcon phone(QPixmap(":/icons/phone.png"));
    static QIcon mail(QPixmap(":/icons/03.png"));
    static QIcon services(QPixmap(":/icons/user.png"));

    if (role == Qt::DisplayRole)
        // return QString::number(section);
        return QSqlQueryModel::headerData(section, orientation, role);

    // return  QAbstractItemModel::headerData(section, orientation, role);
    if (role == Qt::DecorationRole)
        if (section == 0)
            // return qVariantFromValue(services);
            if (role == Qt::DecorationRole)
                if (section == 2)
                    // return qVariantFromValue(mail);
                    // return  QAbstractItemModel::headerData(section, orientation, role);
                    if (role == Qt::DecorationRole)
                        if (section == 1)
                            // return qVariantFromValue(phone);
                            return QAbstractItemModel::headerData(section, orientation, role);
}
