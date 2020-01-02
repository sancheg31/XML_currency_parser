#include "XmlDomHandler.h"
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QLocale>

QVector<QPair<QDate, double>> XmlDomHandler::parse(QByteArray buff) const {
    QLocale german(QLocale::German);
    double valRate(-1);  // курс валюты
    QDate date;
    QVector<QPair<QDate, double>> result;

    QDomDocument doc;
    if (false == doc.setContent(buff))
        throw QString("bad XML-file: setContent");

    QDomElement root = doc.documentElement();
    if (root.tagName() != "ValCurs")
        throw QString("bad XML-file: tagname() != ValCurs");

    QDomNode record_node = root.firstChild();

    while (false == record_node.isNull()) {
        if (record_node.toElement().tagName() != "Record")
            throw QString("bad XML-file: tagname() != Record");
        date = QDate::fromString(record_node.attributes().namedItem("Date").nodeValue(),"dd.MM.yyyy");

        QDomNode node = record_node.firstChild();
        while (false == node.isNull()) {
            if (node.nodeName() == "Value") {
                valRate = german.toDouble(node.toElement().text());
                break;
            }
            node = node.nextSibling();
        }
        result.push_back(QPair{date, valRate});
        record_node = record_node.nextSibling();
    }

    return result;
}
