#include "productsmodel.h"
#include "storage.h"

ProductsModel::ProductsModel(QObject *parent)
    : QAbstractTableModel{parent}
    , m_products{Storage::_().getAllProducts()} {}

int ProductsModel::rowCount(const QModelIndex&) const
{
    return m_products.count();
}

int ProductsModel::columnCount(const QModelIndex&) const
{
    return Product::fieldCount;
}

QVariant ProductsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Vertical)
        return section + 1;

    if (role == Qt::DisplayRole) {
        switch (section) {
        case 0: return "Id";
        case 1: return "Provider Id";
        case 2: return "Name";
        case 3: return "Description";
        case 4: return "Price";
        case 5: return "Amount";
        case 6: return "Unit";
        }
    }
    return {};
}

QVariant ProductsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const auto p = m_products[index.row()];

    if (role == Qt::ToolTipRole && index.column() == 1) {
        return Storage::_().getProviderName(p.providerId);
    }

    if (role == Qt::DisplayRole || role == Qt::ToolTipRole) {
        switch (index.column()) {
        case 0: return p.id;
        case 1: return p.providerId;
        case 2: return p.name;
        case 3: return p.description;
        case 4: return p.price;
        case 5: return p.amount;
        case 6: return Product::unitToStr(p.unit);
        }
    }
    return {};
}

