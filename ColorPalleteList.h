#pragma once

#include <QVector>
#include <QColor>

class ColorPalleteList {
public:
    ColorPalleteList();

    using iterator = QVector<QColor>::iterator;
    using const_iterator = QVector<QColor>::const_iterator;

    QColor operator[](int i) {
        return colors[i];
    }
    const QColor& operator[](int i) const {
        return colors[i];
    }

    int size() const { return colors.size(); }

    iterator begin() { return colors.begin(); }
    const_iterator begin() const { return colors.begin(); }
    iterator end() { return colors.end(); }
    const_iterator end() const { return colors.end(); }

private:
    QVector<QColor> colors;
};

