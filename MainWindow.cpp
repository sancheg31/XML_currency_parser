#include "MainWindow.h"

#include <QtWidgets>

#include "DayScaleDraw.h"
#include "RateReceiver.h"

#include "IXmlHandler.h"
#include "XmlDomHandler.h"
#include "XmlSaxHandler.h"

#include "CurrencyCheckBox.h"

#include <qwt_plot_curve.h>
#include <qwt_plot.h>

MainWindow::MainWindow(const QString& sourceFile, QMainWindow *parent) : QMainWindow(parent),
    load(new QPushButton("load")), from(new QDateEdit(QDate::currentDate().addDays(-1))), to(new QDateEdit(QDate::currentDate())),
    diag(new QwtPlot), menuBar(new QMenuBar()),
    rateReceiver(new RateReceiver(new XmlSaxHandler(), this)), handlerType(HandlerType::SAX) {

    currencyData = CurrencyDataSingleton::instance(sourceFile);
    curButtonGroup = new CurrencyButtonGroup(currencyData, this);
    currentId = currencyData->indexes()[0];
    qDebug() << currentId;
    diag->setAxisScaleDraw(QwtPlot::xBottom, new DayScaleDraw());

    curve.attach(diag);
    curve.setVisible(true);
    curve.setPen(QPen(Qt::red, 2));

    createActionsAndMenus();

    setWindowTitle("Курсы валют");
    setMenuBar(menuBar);

    QGridLayout * mainl = new QGridLayout;
    mainl->addWidget(curButtonGroup, 0, 0, 4, 1);
    mainl->addWidget(from, 0, 2, 1, 2);
    mainl->addWidget(to, 0, 4, 1, 2);
    mainl->addWidget(load, 0, 6, 1, 1);
    mainl->addWidget(diag, 1, 1, 3, 6);

    QWidget * w = new QWidget();
    w->setLayout(mainl);
    setCentralWidget(w);

    connect(load, SIGNAL(clicked()), SLOT(slotLoadClicked()));
    connect(curButtonGroup, SIGNAL(buttonClicked(CurrencyCheckBox*)), this, SLOT(slotCurrencyChanged(CurrencyCheckBox*)));
    connect(rateReceiver, SIGNAL(rate(QDate,double, QString)), SLOT(slotRate(QDate,double, QString)));
    connect(rateReceiver, SIGNAL(loadFinished(QString)), SLOT(slotLoadFinished(QString)));

}

void MainWindow::loadCurrency(const QString &id) {
    int ifrom = from->date().toJulianDay();
    int ito = to->date().toJulianDay();
    int ndays;

    if (ito < ifrom)
        return;

    ndays = ito - ifrom + 1;
    points.clear();
    points.resize(ndays);

    rateReceiver->rateRequest(from->date(), to->date(), id);
}

void MainWindow::slotRate(const QDate &date, const double rate, const QString& id) {
  const qint64 x = date.toJulianDay();
  const qint64 i = x - from->date().toJulianDay();
  points[i] = QPointF(x, rate);
}

void MainWindow::slotLoadFinished(const QString& id) {
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
  qDebug() << "curve set with points on id: " << points.length();
  diag->replot();
}

void MainWindow::slotCurrencyChanged(CurrencyCheckBox* currency) {
    currentId = currency->id();
}

void MainWindow::slotLoadClicked() {
    loadCurrency(currentId);
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











