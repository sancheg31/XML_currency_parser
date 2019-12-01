
#include "ICurrencyValueLexer.h"

class CurrencyValueSax: public ICurrencyValueLexer
{
public:
    virtual ~CurrencyValueSax() override {}
    virtual QHash<QString, double> parse(QByteArray) const override;
};

