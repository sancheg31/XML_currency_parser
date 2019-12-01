#include "RateReceiver.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtXml>

RateReceiver::RateReceiver(IXmlHandler* h, QObject *parent) : QObject(parent), netManager(new QNetworkAccessManager(this)) {
    handler = h;
    connect(netManager, SIGNAL(finished(QNetworkReply*)), SLOT(slotLoad(QNetworkReply*)));
}

void RateReceiver::slotLoad(QNetworkReply *reply) {

    QLocale german(QLocale::German);
    QByteArray buff = reply->readAll();

    /*QXmlStreamReader xmlDoc(buff);

    double valRate(-1);
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
        } else if (token == QXmlStreamReader::EndElement && xmlDoc.name() == "Record") {
            emit rate(date, valRate);
        }
    }*/
    auto result = handler->parse(buff);
    for (auto & el: result)
        emit rate(el.first, el.second);
    emit loadFinished();
    delete reply;

}

void RateReceiver::rateRequest(const QDate &dateBegin, const QDate &dateEnd) {
    QUrlQuery postData;

    QNetworkRequest req(QUrl(QString("http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=" + dateBegin.toString("dd/MM/yyyy") + "&" +
                                   "date_req2=" + dateEnd.toString("dd/MM/yyyy") + "&VAL_NM_RQ=R01020A")));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    netManager->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}
