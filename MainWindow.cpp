#include "MainWindow.h"

#include <QtWidgets>

#include "DayScaleDraw.h"
#include "RateReceiver.h"

#include "IXmlHandler.h"
#include "XmlDomHandler.h"
#include "XmlSaxHandler.h"

#include <qwt_plot_curve.h>
#include <qwt_plot.h>

MainWindow::MainWindow(const QString& sourceFile, QMainWindow *parent) : QMainWindow(parent),
    load(new QPushButton("load")), from(new QDateEdit(QDate::currentDate().addDays(-1))), to(new QDateEdit(QDate::currentDate())),
    diag(new QwtPlot), menuBar(new QMenuBar()),
    rateReceiver(new RateReceiver(new XmlSaxHandler(), this)), handlerType(HandlerType::SAX) {

    currencyData = CurrencyDataSingleton::instance(sourceFile);
    curName = new QLabel(currencyData->name("R01020A"));
    qDebug() << currencyData->name("R01020A");
    diag->setAxisScaleDraw(QwtPlot::xBottom, new DayScaleDraw());

    curve.attach(diag);
    curve.setVisible(true);
    curve.setPen(QPen(Qt::red, 2));

    createActionsAndMenus();

    setWindowTitle("Курсы валют");
    setMenuBar(menuBar);

    QGridLayout * l = new QGridLayout;
    QGridLayout * mainl = new QGridLayout;
    l->addWidget(from, 0, 0, 1, 2);
    l->addWidget(to, 0, 2, 1, 2);
    l->addWidget(curName, 0, 4, 1, 1);
    l->addWidget(load, 0, 5, 1, 1);
    mainl->addLayout(l, 0, 0, 1, 5);
    mainl->addWidget(diag, 1, 0, 3, 5);

    QWidget * w = new QWidget();
    w->setLayout(mainl);
    setCentralWidget(w);

    connect(load, SIGNAL(clicked()), SLOT(slotLoadClicked()));
    connect(rateReceiver, SIGNAL(rate(QDate,double)), SLOT(slotRate(QDate,double)));
    connect(rateReceiver, SIGNAL(loadFinished()), SLOT(slotLoadFinished()));
}

void MainWindow::slotRate(const QDate &date, const double rate) {
  const int x = date.toJulianDay();
  const int i = x - from->date().toJulianDay();
  points[i] = QPointF(x, rate);
}

void MainWindow::slotLoadFinished() {
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

void MainWindow::slotLoadClicked() {
  int ifrom = from->date().toJulianDay(),
      ito = to->date().toJulianDay(),
      ndays;

  if (ito < ifrom)
    return;

  ndays = ito - ifrom + 1;

  points.clear();

  points.resize(ndays);
  rateReceiver->rateRequest(from->date(), to->date());

}

void MainWindow::slotChooseCurrency() {

}

void MainWindow::slotToggleToDom() {
    if (handlerType == HandlerType::SAX) {
        rateReceiver->setXmlHandler(new XmlDomHandler());
        handlerType = HandlerType::DOM;
        dom->setChecked(true);
        sax->setChecked(false);
    }
}

void MainWindow::slotToggleToSax() {
    if (handlerType == HandlerType::DOM) {
        rateReceiver->setXmlHandler(new XmlSaxHandler());
        handlerType = HandlerType::SAX;
        sax->setChecked(true);
        dom->setChecked(false);
    }
}

void MainWindow::createActionsAndMenus() {

    QMenu * currencies = menuBar->addMenu("Currencies");
    currencies->addAction("&Choose currency...", this, SLOT(slotChooseCurrency()));

    QMenu * handler = menuBar->addMenu("Handlers");
    sax = new QAction("SAX");
    connect(sax, SIGNAL(triggered()), this, SLOT(slotToggleToSax()));
    sax->setCheckable(true);
    sax->setChecked(true);
    dom = new QAction("DOM");
    connect(dom, SIGNAL(triggered()), this, SLOT(slotToggleToDom()));
    dom->setCheckable(true);
    dom->setChecked(false);

    handler->addAction(sax);
    handler->addAction(dom);

}











