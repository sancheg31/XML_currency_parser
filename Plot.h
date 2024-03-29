#pragma once

#include <QHash>
#include <QString>

#include <qwt_plot.h>

#include "ColorPalleteList.h"
#include "Curve.h"

class Plot: public QwtPlot
{
public:
    using iterator = QHash<QString, Curve*>::iterator;
    using const_iterator = QHash<QString, Curve*>::const_iterator;

    Plot(const QVector<QString>& indexes);
    Curve* operator[](const QString& ind) {
        return curves[ind];
    }
    const Curve* operator[](const QString& ind) const {
        return curves[ind];
    }
    iterator begin() { return curves.begin(); }
    const_iterator begin() const { return curves.begin(); }
    iterator end() { return curves.end(); }
    const_iterator end() const { return curves.end(); }

public slots:
    virtual void replot() override;

protected:
    Curve* createCurve(QPen pen, QwtSymbol* symbol) const;
    void setPlotSettings();

    QHash<QString, Curve*> curves;
    ColorPalleteList colorList;

};
