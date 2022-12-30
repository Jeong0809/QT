#include <QtTest>
#include <QCoreApplication>
#include <QLineEdit>

// add necessary includes here

class GuiTest : public QObject
{
    Q_OBJECT

public:
    GuiTest();
    ~GuiTest();

private slots:
    void test_case1();
    void test_case1_data();

private:
    QLineEdit *lineEdit;

};

GuiTest::GuiTest()
{

}

GuiTest::~GuiTest()
{

}

void GuiTest::test_case1_data( )
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there+back-again") << list2 << "";
}

void GuiTest::test_case1()
{
    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    events.simulate(lineEdit);

    QCOMPARE(lineEdit->text(), expected);
}

//void GuiTest::test_case1()
//{
//    QTestEventList events;
//    events.addKeyClick('a');
//    events.addKeyClick(Qt::Key_Backspace);
//    events.addDelay(200);

//    events.simulate(lineEdit);
//    QCOMPARE(lineEdit->text(), "");
//    events.simulate(lineEdit);
//    QCOMPARE(lineEdit->text(), " ");

////    QLineEdit lineEdit;
////    QTest::keyClicks(&lineEdit, "hi KDE");
////    QCOMPARE(lineEdit.text(), "hi KDE");
////    QVERIFY2(true, "Failure");
//}

QTEST_MAIN(GuiTest)

#include "tst_guitest.moc"
