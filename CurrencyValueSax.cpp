#include "CurrencyValueSax.h"

#include <QXmlStreamReader>
#include <QLocale>
#include <QDebug>

QHash<QString, double> CurrencyValueSax::parse(QByteArray buf) const {

    QXmlStreamReader xmlDoc(buf);
    QLocale german(QLocale::German);
    QHash<QString, double> values;
    QString currentId;
    double value = 0;

    while (!xmlDoc.atEnd() && !xmlDoc.hasError()) {
        QXmlStreamReader::TokenType token = xmlDoc.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (xmlDoc.name() == "Valute") {
                currentId = xmlDoc.attributes().value("ID").toString();
            }
            else if (xmlDoc.name() == "Value") {
                value = german.toDouble(xmlDoc.readElementText());
            }
        } else if (token == QXmlStreamReader::EndElement) {
            if (xmlDoc.name() == QString("Valute")) {
                values[currentId] = value;
            }
        }
    }

    return values;
}
