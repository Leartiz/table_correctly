#include "providersmodel.h"
#include "storage.h"

ProvidersModel::ProvidersModel(QObject *parent)
    : QAbstractTableModel{parent}
    , m_providers{Storage::_().getAllProviders()} {}

int ProvidersModel::rowCount(const QModelIndex&) const
{
    return m_providers.count();
}

int ProvidersModel::columnCount(const QModelIndex &) const
{
    return Provider::fieldCount;
}

QVariant ProvidersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Vertical)
        return section + 1;

    if (role == Qt::DisplayRole) {
        switch (section) {
        case 0: return "Id";
        case 1: return "Reg Time";
        case 2: return "Name";
        case 3: return "Description";
        case 4: return "Phone Number";
        }
    }
    return {};
}

QVariant ProvidersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const auto p = m_providers[index.row()];

    if (role == Qt::DisplayRole || role == Qt::ToolTipRole) {
        switch (index.column()) {
        case 0: return p.id;
        case 1: return p.regTime.toLocalTime();
        case 2: return p.name;
        case 3: return p.description;
        case 4: return "*****";
        }
    }
    return {};
}

QString ProvidersModel::getPhoneNumber(const int row)
{
    if (row < 0 || row >= m_providers.size()) return {};
    return m_providers[row].phoneNumber;
}
