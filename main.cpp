
#include <QApplication>
#include <QDebug>
#include <QFile>

#include "CurrencyDataSingleton.h"
#include "CurrencyDataLexer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString sourceFile = "D:/Program Files/Notepad++/files/Currencies.xml";
    QString newFile = "D:/Projects/Qt/Currency_graphics/Currencies.xml";
    QString fullFile = "D:/Program Files/Notepad++/files/NewCurrencies.xml";

    CurrencyDataLexer l;
    l.parse(sourceFile);
    auto data = CurrencyDataSingleton::instance(sourceFile);
    auto indexes = data->indexes();


    for (auto & s: indexes)
        qDebug() << s;
    qDebug() << data->name(indexes.first()) << " " << data->name(indexes.back());

    return 0;

}
