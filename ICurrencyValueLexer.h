#pragma once

#include <QVector>
#include <QHash>

class ICurrencyValueLexer
{
public:
    virtual ~ICurrencyValueLexer() {}
    virtual QHash<QString, QString> parse(const QVector<QString>&) const;
};

