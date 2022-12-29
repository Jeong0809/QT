#include "webbrowser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    webbrowser w;
    w.show();
    return a.exec();
}
