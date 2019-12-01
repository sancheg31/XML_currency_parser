#pragma once

#include <QWidget>
#include <QMainWindow>

#include <qwt_plot_curve.h>

#include "CurrencyDataSingleton.h"

class RateReceiver;

namespace Ui {
  class ratesform;
}

class MainWidget : public QWidget {
  Q_OBJECT
public:
  explicit MainWidget(const QString&, QWidget * = nullptr);

public slots:
  void on_loadClicked();
  void on_rate(const QDate& date, const double rate);
  void on_loadFinished();

protected:
  Ui::ratesform *m_pUI;

  CurrencyDataSingleton* currencyData;
  RateReceiver* rateReceiver;
  QwtPlotCurve curve;
  QVector<QPointF> points;
};

