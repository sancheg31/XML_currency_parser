
#include "ICurrencyValueLexer.h"

class CurrencyValueSax : public ICurrencyValueLexer
{
public:
    virtual ~CurrencyValueSax() override {}
    virtual QHash<QString, QString> parse(const QVector<QString> &) const override;
};

