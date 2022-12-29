#include "widget.h"

#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setAge(0);
    QTest::qExec(&w);

    return a.exec();
}
