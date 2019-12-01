#pragma once

#include <QVector>
#include <QHash>
#include <QByteArray>

class ICurrencyValueLexer
{
public:
    virtual ~ICurrencyValueLexer() {}
    virtual QHash<QString, double> parse(QByteArray) const = 0;
};

