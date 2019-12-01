#include "CurrencyDataSingleton.h"

#include "CurrencyDataLexer.h"

CurrencyDataSingleton::CurrencyDataSingleton(const QString& fileName) {
    CurrencyDataLexer lexer;
    lexer.parse(fileName);
    ids = lexer.indexes();
    data = lexer.data();
}
