#pragma once

#include <QVector>
#include <QHash>

#include "CurrencyData.h"

class CurrencyDataSingleton {
public:

    static CurrencyDataSingleton* instance(const QString& str) {
        static CurrencyDataSingleton* instance_ = nullptr;
        if (!instance_)
            instance_ = new CurrencyDataSingleton(str);
        return instance_;
    }

    const QVector<QString>& indexes() const { return ids; }

    QString charCode(const QString& str) const { return data.value(str).charCode; }
    QString name(const QString& str) const { return data.value(str).name; }
    QString numCode(const QString& str) const { return data.value(str).numCode; }

private:
    CurrencyDataSingleton(const QString&);
    CurrencyDataSingleton(const CurrencyDataSingleton&) = delete;
    CurrencyDataSingleton(CurrencyDataSingleton&&) = delete;
    CurrencyDataSingleton& operator=(const CurrencyDataSingleton&) = delete;
    CurrencyDataSingleton& operator=(CurrencyDataSingleton&&) = delete;

    QHash<QString, CurrencyData> data;
    QVector<QString> ids;

};
