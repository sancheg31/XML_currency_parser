#pragma once

#include "IXmlHandler.h"

class XmlDomHandler: public IXmlHandler {
public:
    virtual ~XmlDomHandler() override;
    virtual QVector<QPair<QDate, double>> parse(QByteArray buf) const override;
};

