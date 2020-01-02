#include "CurrencyButtonGroup.h"

#include <QVBoxLayout>

CurrencyButtonGroup::CurrencyButtonGroup(CurrencyDataSingleton* data, QWidget* parent): QWidget(parent), curData(data) {
    QVBoxLayout* l = new QVBoxLayout;
    int i = 0;
    buttonGroup = new QButtonGroup;
    for (auto & s: data->indexes()) {
        auto cur = new CurrencyCheckBox(data->name(s), s);
            buttonGroup->addButton(cur, i++);
            l->addWidget(cur);
    }
    buttonGroup->setExclusive(false);
    setLayout(l);
    connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(slotButtonClicked(QAbstractButton*)));
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotButtonClicked(int)));
}

void CurrencyButtonGroup::slotButtonClicked(QAbstractButton* button) {
    emit buttonClicked(qobject_cast<CurrencyCheckBox*>(button));
}

void CurrencyButtonGroup::slotButtonClicked(int id) {
    emit buttonClicked(id);
}

