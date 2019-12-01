QT += core gui xml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += D:/qwt/qwt-6.1.3/src/
LIBS += -LD:/qwt/qwt-6.1.3/lib/ -lqwt


CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    CurrencyDataLexer.cpp \
    CurrencyDataSingleton.cpp \
    DayScaleDraw.cpp \
    IXmlHandler.cpp \
    MainWidget.cpp \
    MainWindow.cpp \
    RateReceiver.cpp \
    XmlDomHandler.cpp \
    XmlSaxHandler.cpp \
    main.cpp

HEADERS += \
    CurrencyData.h \
    CurrencyDataLexer.h \
    CurrencyDataSingleton.h \
    DayScaleDraw.h \
    IXmlHandler.h \
    MainWidget.h \
    MainWindow.h \
    RateReceiver.h \
    XmlDomHandler.h \
    XmlSaxHandler.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ratesform.ui
