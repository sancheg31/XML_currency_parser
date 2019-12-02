#include "Plot.h"

#include <qwt_plot_magnifier.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>

#include <qwt_picker_machine.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "DayScaleDraw.h"

Plot::Plot(QVector<QString>& indexes) {

    plot = createPlot();
    for (int i = 0; i < indexes.count(); ++i) {
        QwtSymbol * symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush(Qt::yellow), colorList[i], QSize(8, 8));
        curves[indexes[i]] = createCurve(colorList[i%17], symbol);
    }
}

void Plot::replot() {
    QwtPlot::replot();
}

Curve* Plot::createCurve(QPen pen, QwtSymbol* symbol) const {
    Curve* cur = new Curve;
    cur->curve.attach(plot);
    cur->curve.setVisible(true);
    cur->curve.setPen(pen);
    cur->curve.setSymbol(symbol);
    return cur;
}

QwtPlot* Plot::createPlot() const {
    QwtPlot* plot = new QwtPlot;
    plot->setTitle("Graphics");
    plot->setCanvasBackground(Qt::white);
    plot->setAxisTitle(QwtPlot::yLeft, "Value");
    plot->setAxisTitle(QwtPlot::xBottom, "Date");
    plot->setAxisScaleDraw(QwtPlot::xBottom, new DayScaleDraw());
    plot->insertLegend(new QwtLegend());

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::gray, 1));
    grid->attach(plot);

    QwtPlotPicker *picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                                QwtPlotPicker::CrossRubberBand,
                                                QwtPicker::ActiveOnly,
                                                plot->canvas());

    picker->setRubberBandPen(QColor(Qt::black));
    picker->setTrackerPen(QColor(Qt::black));
    picker->setStateMachine(new QwtPickerDragPointMachine());
    return plot;
}




