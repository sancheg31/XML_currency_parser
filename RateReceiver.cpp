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

    auto result = handler->parse(buff);
    for (auto & el: result)
        emit rate(el.first, el.second, currencyId);
    emit loadFinished(currencyId);
    delete reply;

}

void RateReceiver::rateRequest(const QDate &dateBegin, const QDate &dateEnd,  const QString& curId) {
    QUrlQuery postData;
    currencyId = curId;
    QNetworkRequest req(QUrl(QString("http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=" + dateBegin.toString("dd/MM/yyyy") + "&" +
                                   "date_req2=" + dateEnd.toString("dd/MM/yyyy") + "&VAL_NM_RQ=" + currencyId)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    netManager->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}
