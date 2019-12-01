#pragma once

#include <QMainWindow>
#include <qwt_plot_curve.h>

#include "CurrencyDataSingleton.h"
#include "CurrencyButtonGroup.h"

class RateReceiver;
class QPushButton;
class QDateEdit;

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(const QString&, QMainWindow * = nullptr);

  void loadCurrency(const QString& id);
private slots:

  void slotLoadClicked();
  void slotRate(const QDate& date, const double rate, const QString&);
  void slotLoadFinished(const QString&);

  void slotCurrencyChanged(CurrencyCheckBox*);
  void slotToggleToDom();
  void slotToggleToSax();

protected:
  QPushButton* load;
  QDateEdit* from;
  QDateEdit* to;
  QwtPlot* diag;
  CurrencyButtonGroup* curButtonGroup;

  CurrencyDataSingleton* currencyData;
  RateReceiver* rateReceiver;
  QwtPlotCurve curve;
  QVector<QPointF> points;

  QMenuBar* menuBar;

  QAction* sax;
  QAction* dom;

  QString currentId;

  enum HandlerType { SAX, DOM } handlerType;
private:
  void createActionsAndMenus();
  void setCurveSettings();
  void setPlotSettings();
};
