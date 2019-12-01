
#include "ICurrencyValueLexer.h"

class CurrencyValueDom : public ICurrencyValueLexer
{
public:
    virtual ~CurrencyValueDom() override {}
    virtual QHash<QString, double> parse(QByteArray buf) const override;
};

