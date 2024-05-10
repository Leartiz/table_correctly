#ifndef PRODUCTSMODEL_H
#define PRODUCTSMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "models.h"

class ProductsModel : public QAbstractTableModel
{
public:
    explicit ProductsModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QList<Product> m_products;
};

#endif // PRODUCTSMODEL_H
