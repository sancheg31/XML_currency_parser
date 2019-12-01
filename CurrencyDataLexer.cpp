#include "CurrencyDataLexer.h"

#include <QFile>
#include <QHash>
#include <QXmlStreamReader>
#include <QDebug>

void CurrencyDataLexer::parse(const QString& fileName) {
    indexes_.clear();
    data_.clear();
    QFile * inFile = new QFile(fileName);
    if (!inFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QXmlStreamReader xml(inFile);
    QString curCurrencyId = "";
    CurrencyData curData;
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == QString("Valute")) {
                curCurrencyId = xml.attributes().value("ID").toString();
            } else if (xml.name() == QString("NumCode")) {
                curData.numCode = xml.readElementText();
            } else if (xml.name() == QString("CharCode")) {
                curData.charCode = xml.readElementText();
            } else if (xml.name() == QString("Name")) {
                curData.name = xml.readElementText();
            }
        }
        if (token == QXmlStreamReader::EndElement) {
            if (xml.name() == QString("Valute")) {
                data_.insert(curCurrencyId, curData);
                indexes_.push_back(curCurrencyId);
            }
        }
    }
}




