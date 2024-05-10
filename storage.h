#ifndef STORAGE_H
#define STORAGE_H

#include <stdexcept>

#include <QList>
#include <QSqlDatabase>

#include "models.h"

class StorageError : public std::runtime_error {
public:
    explicit StorageError(const QString& text)
        : std::runtime_error(text.toStdString()) {}
};

class Storage
{
public:
    static Storage& _();

    void addProvider(const Provider&) const;
    void addProduct(const Product&) const;

    QList<Product> getAllProducts() const;
    QList<Provider> getAllProviders() const;
    QString getProviderName(quint64 id) const;

    quint64 getProviderCount() const;
    quint64 getProductCount() const;

private:
    void initTablesIfNeeded();
    void initFirstDataIfNeeded();
    Storage();
};

#endif // STORAGE_H
