#pragma once

#include <QString>
#include <QHash>
#include <QVector>

#include "CurrencyData.h"

class CurrencyDataLexer {
public:
    void parse(const QString&);
private:
    QHash<QString, CurrencyData> data;
    QVector<QString> indexes;

};
