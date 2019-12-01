
#pragma once

#include <QObject>
#include <QMap>
#include <QQmlApplicationEngine>

class QNetworkAccessManager;
class QNetworkReply;

class RateReceiver : public QObject {
  Q_OBJECT
public:
  explicit RateReceiver(QObject *parent = nullptr);
signals:
  void rate(const QDate& date, const double &rate);
  void loadFinished();
public slots:
  void rateRequest(const QDate &dateBegin, const QDate &dateEnd);
private slots:
  void on_load(QNetworkReply*);
protected:
  QNetworkAccessManager *m_nam;
};

