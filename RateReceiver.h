
#pragma once

#include <QObject>
#include <QMap>
#include <QQmlApplicationEngine>

#include "IXmlHandler.h"

class QNetworkAccessManager;
class QNetworkReply;

class RateReceiver : public QObject {
  Q_OBJECT
public:
    explicit RateReceiver(IXmlHandler*, QObject *parent = nullptr);
    void setXmlHandler(IXmlHandler* h) { if (handler) delete handler; handler = h; }
    IXmlHandler* xmlHandler() const { return handler; }
signals:
    void rate(const QDate& date, const double &rate);
    void loadFinished();

public slots:
    void rateRequest(const QDate &dateBegin, const QDate &dateEnd);

private slots:
    void slotLoad(QNetworkReply*);

protected:
    QNetworkAccessManager *netManager;
    IXmlHandler * handler;

};

