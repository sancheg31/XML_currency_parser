
#include <QApplication>

#include "MainWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString sourceFile = "D:/Projects/Program Files/Notepad++/files/Currencies.xml";
    MainWidget w(sourceFile);
    w.show();

    return app.exec();
}
