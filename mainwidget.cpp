#include "MainWidget.h"

#include "ui_ratesform.h"

#include "DayScaleDraw.h"
#include "RateReceiver.h"

#include "IXmlHandler.h"
#include "XmlSaxHandler.h"

#include <qwt_plot_curve.h>

MainWidget::MainWidget(const QString& sourceFile, QWidget *parent) : QWidget(parent),
  m_pUI(new Ui::ratesform), currencyData(CurrencyDataSingleton::instance(sourceFile)),
  rateReceiver(new RateReceiver(new XmlSaxHandler(), this)) {
  m_pUI->setupUi(this);

  m_pUI->from->setDate(QDate::currentDate().addDays(-1));
  m_pUI->to->setDate(QDate::currentDate());

  m_pUI->diag->setAxisScaleDraw(QwtPlot::xBottom, new DayScaleDraw());

  curve.attach(m_pUI->diag);
  curve.setVisible(true);
  curve.setPen(QPen(Qt::red, 2));

  connect(m_pUI->load, SIGNAL(clicked()), SLOT(on_loadClicked()));
  connect(rateReceiver, SIGNAL(rate(QDate,double)), SLOT(on_rate(QDate,double)));
  connect(rateReceiver, SIGNAL(loadFinished()), SLOT(on_loadFinished()));
}

void MainWidget::on_rate(const QDate &date, const double rate) {
  const int x = date.toJulianDay();
  const int i = x - m_pUI->from->date().toJulianDay();
  points[i] = QPointF(x, rate);
}

void MainWidget::on_loadFinished() {
  int n = points.length();
  int i = 0;

  while (i < n) {
    if (0 == points[i].x()) {
      points.removeAt(i);
      --n;
    }
    else
      ++i;
  }

  curve.setSamples(points);
  qDebug() << "curve set with points: " << points.length();
  m_pUI->diag->replot();
}

void MainWidget::on_loadClicked() {
  int
      ifrom = m_pUI->from->date().toJulianDay(),
      ito = m_pUI->to->date().toJulianDay(),
      ndays;

  if (ito < ifrom)
    return;

  ndays = ito - ifrom + 1;

  points.clear();

  points.resize(ndays);
  rateReceiver->rateRequest(m_pUI->from->date(), m_pUI->to->date());

}
