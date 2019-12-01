#include "GraphMainWindow.h"
#include "Lexer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lexer l;
    l.parse("D:/Program Files/Notepad++/files/Currencies.xml");
    return 0;
}
