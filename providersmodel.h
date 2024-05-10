#ifndef PROVIDERSMODEL_H
#define PROVIDERSMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "models.h"

class ProvidersModel : public QAbstractTableModel
{
public:
    explicit ProvidersModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

public:
    QString getPhoneNumber(const int row);

private:
    QList<Provider> m_providers;
};

#endif // PROVIDERSMODEL_H
