#include "Plot.h"

#include <qwt_plot_magnifier.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>

#include <qwt_picker_machine.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "DayScaleDraw.h"

Plot::Plot(const QVector<QString>& indexes) {

    setPlotSettings();
    for (int i = 0; i < indexes.count(); ++i) {
        QwtSymbol * symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush(Qt::yellow), QPen(Qt::black), QSize(6, 6));
        curves[indexes[i]] = createCurve(QPen(colorList[i%colorList.size()], 4), symbol);
    }
}

void Plot::replot() {
    QwtPlot::replot();
}

Curve* Plot::createCurve(QPen pen, QwtSymbol* symbol) const {
    Curve* cur = new Curve;
    cur->curve.setVisible(true);
    cur->curve.setPen(pen);
    cur->curve.setSymbol(symbol);
    return cur;
}

void Plot::setPlotSettings() {
    setTitle("Graphics");
    setCanvasBackground(Qt::white);
    setAxisTitle(QwtPlot::yLeft, "Value");
    setAxisTitle(QwtPlot::xBottom, "Date");
    setAxisScaleDraw(QwtPlot::xBottom, new DayScaleDraw());
    insertLegend(new QwtLegend());

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::gray, 1));
    grid->attach(this);

    QwtPlotPicker *picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                                QwtPlotPicker::CrossRubberBand,
                                                QwtPicker::ActiveOnly,
                                                canvas());

    //QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(canvas());
    //magnifier->setMouseButton(Qt::MidButton);

    //QwtPlotPanner *panner = new QwtPlotPanner(canvas());
    //panner->setMouseButton( Qt::RightButton );

    picker->setRubberBandPen(QColor(Qt::black));
    picker->setTrackerPen(QColor(Qt::black));
    picker->setStateMachine(new QwtPickerDragPointMachine());
}




