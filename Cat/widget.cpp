#include "widget.h"
#include <QDebug>

Widget::Widget(QObject *parent)
    : QObject(parent)
{
}

void Widget::test()
{
    qInfo() << "test";
}

void Widget::meow()
{
    qInfo() << "meow";
}

void Widget::sleep()
{
    qInfo() << "sleep";
}

void Widget::speak(QString value)
{
    qInfo() << "speak: " << value;
}

Widget::~Widget()
{
}










