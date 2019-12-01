#pragma once

#include <QHash>

class CurrencyContainer: public QHash<QString, double> {
public:
    CurrencyContainer(): QHash<QString, double>() {}
    CurrencyContainer(const CurrencyContainer& ob): QHash<QString, double>(ob) {}
private:
};
