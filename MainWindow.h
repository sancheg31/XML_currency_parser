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

private slots:

  void slotLoadClicked();
  void slotRate(const QDate& date, const double rate);
  void slotLoadFinished();

  void slotToggleToDom();
  void slotToggleToSax();
  void slotChooseCurrency();

protected:
  QPushButton* load;
  QDateEdit* from;
  QDateEdit* to;
  QwtPlot* diag;

  QMenuBar* menuBar;
  CurrencyDataSingleton* currencyData;
  RateReceiver* rateReceiver;
  QwtPlotCurve curve;
  QVector<QPointF> points;

  QAction* sax;
  QAction* dom;

  enum HandlerType { SAX, DOM } handlerType;
private:
  void createActionsAndMenus();
};
