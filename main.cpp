
#include <QApplication>
#include <QDebug>
#include <QFile>

#include "CurrencyContainer.h"
#include "CurrencyDataSingleton.h"
#include "CurrencyDataLexer.h"
#include "CurrencyValueSax.h"

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
    CurrencyValueSax saxLexer;

    QFile * inFile = new QFile(fullFile);
    inFile->open(QFile::ReadOnly | QFile::Text);

    auto values = saxLexer.parse(inFile->readAll());

    inFile->close();

    for (auto & v: values)
        qDebug() << v;

    return 0;

}
