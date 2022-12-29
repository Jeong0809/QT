#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtTest/QtTest>
#include <QTest>

class Widget : public QObject
{
    Q_OBJECT

public:
    explicit Widget(QObject *parent = nullptr);
    ~Widget();
    void test();

private slots:
    void meow();
    void sleep();
    void speak(QString value);
};
#endif // WIDGET_H
