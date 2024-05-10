#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>

#include "storage.h"

namespace
{

void createTableIfNeeded(const QString& textQuery, const QString& tableName = {})
{
    QSqlQuery q;
    if (!q.prepare(textQuery)) {
        throw std::runtime_error(
            QString("prepare query failed [table `%1`]").
                arg(tableName).toStdString());
    }

    if (!q.exec()) {
        throw std::runtime_error(
            QString("exec query failed [table `%1`]").
                arg(tableName).toStdString());
    }
}

quint64 getCount(const QString& tableName)
{
    QSqlQuery q;
    QString tq = "SELECT COUNT(*) FROM " + tableName + ";";

    if (!q.prepare(tq) || !q.exec() || !q.first()) {
        throw StorageError(q.lastError().text());
    }

    bool converted = false;
    const auto count = q.value(0).toULongLong(&converted);
    if (!converted) {
        throw StorageError(tableName + " count convert failed");
    }
    return count;
}

}

// -----------------------------------------------------------------------

Storage::Storage()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("storage.sqlite");

    if (!db.open()) {
        throw std::runtime_error("open database failed");
    }

    initTablesIfNeeded();
    initFirstDataIfNeeded();
}

void Storage::initTablesIfNeeded()
{
    const auto provider = QString(
        "CREATE TABLE IF NOT EXISTS Provider ( "
        "    Id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "    RegTime TEXT NOT NULL, "
        "    Name TEXT NOT NULL, "
        "    Description TEXT NOT NULL, "
        "    PhoneNumber TEXT NOT NULL "
        ");"
    );
    const auto product = QString(
        "CREATE TABLE IF NOT EXISTS Product ( "
        "    Id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "    ProviderId INTEGER NOT NULL, "
        "    Name TEXT NOT NULL, "
        "    Description TEXT NOT NULL, "
        "    Price REAL NOT NULL, "
        "    Amount INTEGER NOT NULL, "
        "    Unit INTEGER NOT NULL, "

        "    FOREIGN KEY (ProviderId)  REFERENCES Provider(Id) "
        ");"
    );

    createTableIfNeeded(provider, "Provider");
    createTableIfNeeded(product, "Product");
}

void Storage::initFirstDataIfNeeded()
{
    if (getProviderCount() == 0) {
        addProvider(Provider{0, QDateTime::currentDateTime(),
                             "Apple",
                             "Apple Inc. is an American multinational technology company headquartered in Cupertino, California.",
                             "1-800-MY-APPLE"});
        addProvider(Provider{0, QDateTime::currentDateTime(),
                             "Samsung",
                             "Samsung Electronics Co., Ltd. is a South Korean multinational electronics company headquartered in Samsung Town, Seoul.",
                             "1-800-SAMSUNG"});
        //...
    }

    if (getProductCount() == 0) {
        addProduct(Product{0, 1,
                           "iPhone 14 Pro",
                           "The iPhone 14 Pro is a high-end smartphone designed, developed, and marketed by Apple Inc.",
                           999.00, 50, Product::piece});
        addProduct(Product{0, 1,
                           "MacBook Air M2",
                           "The MacBook Air M2 is a laptop designed, developed, and marketed by Apple Inc.",
                           1099.00, 30, Product::piece});
        addProduct(Product{0, 2,
                           "Galaxy S23 Ultra",
                           "The Galaxy S23 Ultra is a high-end smartphone designed, developed, and marketed by Samsung Electronics.",
                           1199.00, 40, Product::piece});
        //...
    }
}

Storage& Storage::_()
{
    static Storage _;
    return _;
}

// -----------------------------------------------------------------------

void Storage::addProvider(const Provider& p) const
{
    const QString tq = "INSERT INTO Provider (RegTime, Name, Description, PhoneNumber) VALUES "
                       "(?, ?, ?, ?);";
    QSqlQuery q;
    if (!q.prepare(tq)) {
        throw StorageError(q.lastError().text()); // ?
    }
    q.addBindValue(p.regTime.toUTC().toString(Qt::DateFormat::ISODate));
    q.addBindValue(p.name);
    q.addBindValue(p.description);
    q.addBindValue(p.phoneNumber);
    if (!q.exec()) {
        throw StorageError(q.lastError().text()); // ?
    }
}

void Storage::addProduct(const Product& p) const
{
    const QString tq = "INSERT INTO Product (ProviderId, Name, Description, Price, Amount, Unit) VALUES "
                       "(?, ?, ?, ?, ?, ?)";
    QSqlQuery q;
    if (!q.prepare(tq)) {
        throw StorageError(q.lastError().text());
    }
    q.addBindValue(p.providerId);
    q.addBindValue(p.name);
    q.addBindValue(p.description);
    q.addBindValue(p.price);
    q.addBindValue(p.amount);
    q.addBindValue(p.unit);
    if (!q.exec()) {
        throw StorageError(q.lastError().text());
    }
}

QList<Provider> Storage::getAllProviders() const
{
    const QString tq = "SELECT * FROM Provider;";
    QSqlQuery q;
    if (!q.prepare(tq) || !q.exec()) {
        throw StorageError(q.lastError().text());
    }

    QList<Provider> providers;
    while (q.next()) {
        Provider p;
        p.id = q.value(0).toULongLong();
        p.regTime = q.value(1).toDateTime();
        p.name = q.value(2).toString();
        p.description = q.value(3).toString();
        p.phoneNumber = q.value(4).toString();
        providers.push_back(p);
    }
    return providers;
}

QString Storage::getProviderName(quint64 id) const
{
    const auto tq = QString("SELECT Name FROM Provider WHERE Id = %1;").arg(id);
    QSqlQuery q;
    if (!q.prepare(tq) || !q.exec() || !q.first()) {
        throw StorageError(q.lastError().text());
    }

    return q.value(0).toString();
}

QList<Product> Storage::getAllProducts() const
{
    const QString tq = "SELECT * FROM Product;";
    QSqlQuery q;
    if (!q.prepare(tq) || !q.exec()) {
        throw StorageError(q.lastError().text());
    }

    QList<Product> products;
    while (q.next()) {
        Product p;
        p.id = q.value(0).toULongLong();
        p.providerId = q.value(1).toULongLong();
        p.name = q.value(2).toString();
        p.description = q.value(3).toString();
        p.price = q.value(4).toDouble();
        p.amount = q.value(5).toULongLong();
        p.unit = Product::Unit(q.value(6).toInt());
        products.push_back(p);
    }
    return products;
}

quint64 Storage::getProviderCount() const
{
    return getCount("Provider");
}

quint64 Storage::getProductCount() const
{
    return getCount("Product");
}
