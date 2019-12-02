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
        emit rate(el.first, el.second, currencyId.head());
    qDebug() << "RateReceiver::slotLoad(): emiting loadFinished with id: " << currencyId.head();
    emit loadFinished(currencyId.head(), currencyId.size() == 1);
    currencyId.dequeue();
    qDebug() << "RateReceiver::slotLoad(): queue size is :" << currencyId.size();
    delete reply;

}

void RateReceiver::rateRequest(const QDate &dateBegin, const QDate &dateEnd,  const QString& curId) {
    currencyId.enqueue(curId);
    QUrlQuery postData;
    qDebug() << "rateReceiver::rateRequest(): loading currency with id: " << currencyId.head();
    QNetworkRequest req(QUrl(QString("http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=" + dateBegin.toString("dd/MM/yyyy") + "&" +
                                   "date_req2=" + dateEnd.toString("dd/MM/yyyy") + "&VAL_NM_RQ=" + curId)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    netManager->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}
