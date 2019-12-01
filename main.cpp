
#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString sourceFile = "D:/Projects/Qt/Currency_graphics/Currencies.xml";

    MainWindow m(sourceFile);
    m.show();

    return app.exec();
}
