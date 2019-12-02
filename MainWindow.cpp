#include "MainWindow.h"

#include <QtWidgets>

#include "DayScaleDraw.h"
#include "RateReceiver.h"

#include "IXmlHandler.h"
#include "XmlDomHandler.h"
#include "XmlSaxHandler.h"

#include "CurrencyCheckBox.h"

#include <qwt_plot.h>

#include <qwt_plot_magnifier.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>

#include <qwt_picker_machine.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

MainWindow::MainWindow(const QString& sourceFile, QMainWindow *parent) : QMainWindow(parent),
    load(new QPushButton("load")), from(new QDateEdit(QDate::currentDate().addDays(-2))),
    to(new QDateEdit(QDate::currentDate().addDays(-1))), menuBar(new QMenuBar()),
    rateReceiver(new RateReceiver(new XmlSaxHandler(), this)), handlerType(HandlerType::SAX) {

    currencyData = CurrencyDataSingleton::instance(sourceFile);
    plot  = new Plot(currencyData->indexes());
    curButtonGroup = new CurrencyButtonGroup(currencyData, this);

    createActionsAndMenus();
    setWindowTitle("Курсы валют");
    setMenuBar(menuBar);

    QGridLayout * mainl = new QGridLayout;
    mainl->addWidget(curButtonGroup, 0, 0, 4, 1);
    mainl->addWidget(from, 0, 2, 1, 2);
    mainl->addWidget(to, 0, 4, 1, 2);
    mainl->addWidget(load, 0, 6, 1, 1);
    mainl->addWidget(plot, 1, 1, 3, 6);

    QWidget * w = new QWidget();
    w->setLayout(mainl);
    setCentralWidget(w);

    connect(load, SIGNAL(clicked()), SLOT(slotLoadClicked()));
    connect(curButtonGroup, SIGNAL(buttonClicked(CurrencyCheckBox*)), this, SLOT(slotCurrencyButtonClicked(CurrencyCheckBox*)));
    connect(rateReceiver, SIGNAL(rate(QDate,double, QString)), SLOT(slotRate(QDate,double, QString)));
    connect(rateReceiver, SIGNAL(loadFinished(QString, bool)), SLOT(slotLoadFinished(QString, bool)));

}

void MainWindow::loadCurrency(const QString &id) {
    qint64 ifrom = from->date().toJulianDay();
    qint64 ito = to->date().toJulianDay();

    if (ito < ifrom || from->date() == QDate::currentDate())
        return;

    qint64 ndays = ito - ifrom + 1;

    (*plot)[id]->points.clear();
    (*plot)[id]->points.resize(ndays);
    (*plot)[id]->curve.setTitle(currencyData->name(id));

    qDebug() << "MainWindow::loadCurrency(): load currency with id: " << id;
    rateReceiver->rateRequest(from->date(), to->date(), id);
}

void MainWindow::slotRate(const QDate &date, const double rate, const QString& id) {
    const qint64 x = date.toJulianDay();
    const qint64 i = x - from->date().toJulianDay();
    (*plot)[id]->points[i] = QPointF(x, rate);
}

void MainWindow::slotLoadFinished(const QString& id, bool b) {

    int n = (*plot)[id]->points.length();
    int i = 0;

    while (i < n) {
    if (0 == (*plot)[id]->points[i].x()) {
      (*plot)[id]->points.removeAt(i);
      --n;
    }
    else
      ++i;
    }
    (*plot)[id]->curve.setSamples((*plot)[id]->points);
    qDebug() << "MainWindow::slotLoadFinished(): curve set with points " << (*plot)[id]->points.size() << " on id " << id;
    plot->replot();
    load->setEnabled(b);

}

void MainWindow::slotCurrencyButtonClicked(CurrencyCheckBox* currency) {
    if (!currency->isChecked()) {
        (*plot)[currency->id()]->curve.detach();
        (*plot)[currency->id()]->points.clear();
        plot->replot();
    }
    else {
        (*plot)[currency->id()]->curve.attach(plot);
        loadCurrency(currency->id());
        plot->replot();
    }
}

void MainWindow::slotLoadClicked() {
    load->setEnabled(false);
    bool b = true;
    for (auto & x: currencyData->indexes()) {
        (*plot)[x]->curve.detach();
        (*plot)[x]->points.clear();
    }
    plot->replot();
    for (int i = 0; i < currencyData->indexes().count(); ++i) {
        auto button = curButtonGroup->group()->button(i);
        if (button->isChecked()) {
            bool b = false;
            auto cur = qobject_cast<CurrencyCheckBox*>(button);
            qDebug() << cur->id() << " " << cur->name();
            loadCurrency(cur->id());
            QTimer wait;
            wait.start(30);
            (*plot)[cur->id()]->curve.attach(plot);
        }
    }
    plot->replot();
    load->setEnabled(b);
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







