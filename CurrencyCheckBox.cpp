#include "CurrencyCheckBox.h"

CurrencyCheckBox::CurrencyCheckBox(const QString& name, const QString& id, QWidget* parent): QCheckBox(parent),
    curId(id), curName(name)  {
    connect(this, SIGNAL(stateChanged(int)), this, SLOT(slotStateChanged(int)));
    setText(name);
}

void CurrencyCheckBox::slotStateChanged(int state) {
    emit stateChanged(curId, state);
}

