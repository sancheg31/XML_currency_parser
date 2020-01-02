#pragma once
#include <qwt_scale_draw.h>

class DayScaleDraw : public QwtScaleDraw {
public:
    DayScaleDraw() {}
    virtual QwtText label(double v) const;
};

