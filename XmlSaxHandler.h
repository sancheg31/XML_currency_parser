#pragma once

#include "IXmlHandler.h"

class XmlSaxHandler: public IXmlHandler {
public:
    virtual ~XmlSaxHandler() override;
    virtual QVector<QPair<QDate, double>> parse(QByteArray buf) const override;
};
