#include "edit.h"
#include <QTime>
#include <QTimeEdit>
#include <QDate>
#include <QDateEdit>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTimeEdit* timeEdit = new QTimeEdit(0);
    timeEdit->setTime(QTime::currentTime());
    timeEdit->show();

    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->show();

    return a.exec();
}
