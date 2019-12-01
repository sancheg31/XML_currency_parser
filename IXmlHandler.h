#pragma once

#include <QVector>
#include <QPair>
#include <QDate>
#include <QByteArray>

class IXmlHandler {
public:
    virtual ~IXmlHandler() {}
    virtual QVector<QPair<QDate, double>> parse(QByteArray buf) const = 0;
};

