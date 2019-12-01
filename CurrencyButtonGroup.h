#pragma once

#include <QWidget>
#include <QButtonGroup>

#include "CurrencyDataSingleton.h"
#include "CurrencyCheckBox.h"

class CurrencyButtonGroup: public QWidget {
    Q_OBJECT
public:
    CurrencyButtonGroup(CurrencyDataSingleton* data, QWidget* = nullptr);
    QButtonGroup* group() const { return buttonGroup; }
signals:
    void buttonClicked(CurrencyCheckBox*);

private slots:
    void slotButtonClicked(QAbstractButton*);
private:
    QButtonGroup* buttonGroup;
    CurrencyDataSingleton* curData;
};

