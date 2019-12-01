#include "MainWindow.h"

#include <QtWidgets>

#include "DayScaleDraw.h"
#include "RateReceiver.h"

#include <qwt_plot_curve.h>
#include <qwt_plot.h>

MainWindow::MainWindow(const QString& sourceFile, QMainWindow *parent) : QMainWindow(parent),
    load(new QPushButton("load")), from(new QDateEdit(QDate::currentDate().addDays(-1))), to(new QDateEdit(QDate::currentDate())),
    diag(new QwtPlot), currencyData(CurrencyDataSingleton::instance(sourceFile)), rateReceiver(new RateReceiver(this)) {

    diag->setAxisScaleDraw(QwtPlot::xBottom, new DayScaleDraw());
    setWindowTitle("Курсы валют");

    QHBoxLayout * l = new QHBoxLayout;
    QGridLayout * mainl = new QGridLayout;
    l->addWidget(from);
    l->addWidget(to);
    l->addWidget(load);
    mainl->addLayout(l, 0, 0, 1, 3);
    mainl->addWidget(diag, 1, 0, 3, 3);

    QWidget * w = new QWidget();
    w->setLayout(mainl);
    setCentralWidget(w);

    curve.attach(diag);
    curve.setVisible(true);
    curve.setPen(QPen(Qt::red, 2));

    connect(load, SIGNAL(clicked()), SLOT(on_loadClicked()));
    connect(rateReceiver, SIGNAL(rate(QDate,double)), SLOT(on_rate(QDate,double)));
    connect(rateReceiver, SIGNAL(loadFinished()), SLOT(on_loadFinished()));
}

void MainWindow::on_rate(const QDate &date, const double rate) {
  const int x = date.toJulianDay();
  const int i = x - from->date().toJulianDay();
  points[i] = QPointF(x, rate);
}

void MainWindow::on_loadFinished() {
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
  diag->replot();
}

void MainWindow::on_loadClicked() {
  int
      ifrom = from->date().toJulianDay(),
      ito = to->date().toJulianDay(),
      ndays;

  if (ito < ifrom)
    return;

  ndays = ito - ifrom + 1;

  points.clear();

  points.resize(ndays);
  rateReceiver->rateRequest(from->date(), to->date());

}
