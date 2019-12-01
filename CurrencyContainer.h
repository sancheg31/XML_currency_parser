#pragma once

#include <QHash>

class CurrencyContainer: public QHash<QString, double> {
public:
    CurrencyContainer() {}
    CurrencyContainer(const CurrencyContainer& ob): values(ob.values) {}
private:
    QHash<QString, double> values;
};
