#include "RateReceiver.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtXml>

RateReceiver::RateReceiver(QObject *parent) : QObject(parent), m_nam(new QNetworkAccessManager(this)) {
  connect(m_nam, SIGNAL(finished(QNetworkReply*)), SLOT(on_load(QNetworkReply*)));
}

void RateReceiver::on_load(QNetworkReply *reply) {

    QLocale german(QLocale::German);
    QByteArray buff = reply->readAll();
    QXmlStreamReader xmlDoc(buff);

    qDebug() << buff;

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
    }
    emit loadFinished();
    delete reply;

}

void RateReceiver::rateRequest(const QDate &dateBegin, const QDate &dateEnd) {
  QUrlQuery postData;

  QNetworkRequest req(QUrl(QString("http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=" + dateBegin.toString("dd/MM/yyyy") + "&" +
                                   "date_req2=" + dateEnd.toString("dd/MM/yyyy") + "&VAL_NM_RQ=R01020A")));
  req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  m_nam->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}
