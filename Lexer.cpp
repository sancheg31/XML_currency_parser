#include "Lexer.h"

#include <QFile>
#include <QHash>
#include <QXmlStreamReader>
#include <QDebug>

struct CurrencyData {
public:
    QString name;
    QString charCode;
    QString numCode;
};

void Lexer::parse(const QString& fileName) const {

    QHash<QString, CurrencyData> currencies;
    QVector<QString> ids;
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
                currencies.insert(curCurrencyId, curData);
                ids.push_back(curCurrencyId);
            }
        }
    }
    QFile* outFile = new QFile("D:/Projects/Qt/Currency_graphics/Currencies.xml");
    if (!outFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QXmlStreamWriter writer(outFile);
    writer.writeStartDocument("1.0", true);

    for (auto & id: ids) {
        CurrencyData el = currencies[id];
        writer.writeCharacters("\n\t");
        writer.writeStartElement("Valute");
        writer.writeCharacters("\n\t\t");
        writer.writeTextElement("ID", id);
        writer.writeCharacters("\n\t\t");
        writer.writeTextElement("name", el.name);
        writer.writeCharacters("\n\t\t");
        writer.writeTextElement("CharCode", el.charCode);
        writer.writeCharacters("\n\t\t");
        writer.writeTextElement("NumCode", el.numCode);
        writer.writeCharacters("\n\t");
        writer.writeEndElement();
    }
    writer.writeEndDocument();
    outFile->close();
}




