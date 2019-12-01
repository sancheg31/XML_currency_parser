#include "DayScaleDraw.h"
#include <QTime>

QwtText DayScaleDraw::label(double v) const {
  return QDate::fromJulianDay(v).toString("dd.MM.yy");
}
