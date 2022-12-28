#include "qteditor.h"
#include <QTranslator>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("Translator_ko");
    a.installTranslator(&translator);

    QtEditor w;
    w.show();
    return a.exec();
}
