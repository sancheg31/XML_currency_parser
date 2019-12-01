#include "XmlSaxHandler.h"

#include <QXmlStreamReader>
#include <QDebug>
#include <QDate>

QVector<QPair<QDate, double>> XmlSaxHandler::parse(QByteArray buff) const {
    QLocale german(QLocale::German);
    QXmlStreamReader xmlDoc(buff);
    QVector<QPair<QDate, double>> result;
    qDebug() << buff;

    double valRate = -1; // курс валюты
    QDate date;
    while (!xmlDoc.atEnd() && !xmlDoc.hasError()) {
        QXmlStreamReader::TokenType token = xmlDoc.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (xmlDoc.name() == "Record") {
                QXmlStreamAttributes attrib = xmlDoc.attributes();
                date = QDate::fromString(attrib.value("Date").toString(), "dd.MM.yyyy");
            }
            if (xmlDoc.name() == "Value") {
                valRate = german.toDouble(xmlDoc.readElementText());
                continue;
            }
        }
        if (token == QXmlStreamReader::EndElement && xmlDoc.name() == "Record") {
            result.push_back(QPair{date, valRate});
        }
    }
    return result;
}
