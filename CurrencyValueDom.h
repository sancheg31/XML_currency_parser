
#include "ICurrencyValueLexer.h"

class CurrencyValueDom : public ICurrencyValueLexer
{
public:
    virtual ~CurrencyValueDom() override {}
    virtual QHash<QString, QString> parse(const QVector<QString> &) const override;
};

