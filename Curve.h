#pragma once

#include <qwt_plot_curve.h>
#include <QPointF>

struct Curve {
public:
    QwtPlotCurve curve_;
    QVector<QPointF> points_;


};
