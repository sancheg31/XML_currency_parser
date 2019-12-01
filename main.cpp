
#include <QApplication>
#include <QDebug>

#include "CurrencyContainer.h"
#include "CurrencyDataSingleton.h"
#include "CurrencyDataLexer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString sourceFile = "D:/Program Files/Notepad++/files/Currencies.xml";
    QString newFile = "D:/Projects/Qt/Currency_graphics/Currencies.xml";
    CurrencyDataLexer l;
    l.parse(sourceFile);
    auto data = CurrencyDataSingleton::instance(sourceFile);
    auto indexes = data->indexes();
    for (auto & s: indexes)
        qDebug() << s;
    qDebug() << data->name(indexes[0]) << " " << data->name(indexes.back());
    return 0;
}
