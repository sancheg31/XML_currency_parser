#pragma once

#include <QCheckBox>

class CurrencyCheckBox: public QCheckBox {
    Q_OBJECT
public:
    CurrencyCheckBox(const QString& name, const QString& id, QWidget* = nullptr);

    const QString& id() const { return curId; }
    const QString& name() const { return curName; }

signals:
    void stateChanged(const QString&, int);

private slots:
    void slotStateChanged(int);

private:
    QString curId;
    QString curName;
};

