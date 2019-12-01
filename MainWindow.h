#pragma once

#include <QMainWindow>
#include <qwt_plot_curve.h>

#include "CurrencyDataSingleton.h"

class RateReceiver;
class QPushButton;
class QDateEdit;

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(const QString&, QMainWindow * = nullptr);

public slots:
  void on_loadClicked();
  void on_rate(const QDate& date, const double rate);
  void on_loadFinished();

protected:
  QPushButton* load;
  QDateEdit* from;
  QDateEdit* to;
  QwtPlot* diag;

  CurrencyDataSingleton* currencyData;
  RateReceiver* rateReceiver;
  QwtPlotCurve curve;
  QVector<QPointF> points;
};
