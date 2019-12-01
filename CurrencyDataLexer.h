#pragma once

#include <QString>
#include <QHash>
#include <QVector>

#include "CurrencyData.h"

class CurrencyDataLexer {
public:
    const QVector<QString>& indexes() const { return indexes_; }
    const QHash<QString, CurrencyData>& data() const { return data_; }
    void parse(const QString&);
private:
    QVector<QString> indexes_;
    QHash<QString, CurrencyData> data_;


};
