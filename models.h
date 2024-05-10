#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QDateTime>

struct Product {
    static const int fieldCount = 7;

    enum Unit : int {
        piece, gram,
        //...
    };

    static QString unitToStr(Unit val) {
        switch (val) {
        case piece: return "piece";
        case gram: return "gram";
        }
        return {};
    }

    quint64 id;
    quint64 providerId;
    QString name;
    QString description;
    double price;

    quint64 amount;
    Unit unit;
};

struct Provider {
    static const int fieldCount = 5;

    quint64 id;
    QDateTime regTime;
    QString name;
    QString description;
    QString phoneNumber;
};

#endif // MODELS_H
