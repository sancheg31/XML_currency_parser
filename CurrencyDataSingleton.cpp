#include "CurrencyDataSingleton.h"

#include <QFile>
#include <QXmlStreamReader>

CurrencyDataSingleton::CurrencyDataSingleton(const QString& fileName) {
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
                if (curCurrencyId != "") {
                    data.insert(curCurrencyId, curData);
                    ids.push_back(curCurrencyId);
                }
                curCurrencyId = xml.attributes().value("ID").toString();
            } else if (xml.name() == QString("NumCode")) {
                curData.numCode = xml.readElementText();
            } else if (xml.name() == QString("CharCode")) {
                curData.charCode = xml.readElementText();
            } else if (xml.name() == QString("Name")) {
                curData.name = xml.readElementText();
            }
        }
    }

}
