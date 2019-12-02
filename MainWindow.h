#pragma once

#include <QMainWindow>
#include <qwt_plot_curve.h>

#include "CurrencyDataSingleton.h"
#include "CurrencyButtonGroup.h"

#include "Plot.h"

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
  void slotLoadFinished(const QString&, bool);

  void slotCurrencyButtonClicked(CurrencyCheckBox*);
  void slotToggleToDom();
  void slotToggleToSax();

protected:

  QPushButton* load;
  QDateEdit* from;
  QDateEdit* to;
  CurrencyButtonGroup* curButtonGroup;

  CurrencyDataSingleton* currencyData;
  RateReceiver* rateReceiver;

  Plot * plot;

  QMenuBar* menuBar;

  QAction* sax;
  QAction* dom;

  enum HandlerType { SAX, DOM } handlerType;
  void createActionsAndMenus();

};
