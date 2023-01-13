/********************************************************************************
** Form generated from reading UI file 'patientinfo.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTINFO_H
#define UI_PATIENTINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientInfo
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTableWidget *tableWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;

    void setupUi(QWidget *PatientInfo)
    {
        if (PatientInfo->objectName().isEmpty())
            PatientInfo->setObjectName("PatientInfo");
        PatientInfo->resize(300, 553);
        PatientInfo->setMaximumSize(QSize(300, 16777215));
        gridLayout = new QGridLayout(PatientInfo);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(PatientInfo);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tableWidget_2 = new QTableWidget(PatientInfo);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_2->setObjectName("tableWidget_2");

        gridLayout->addWidget(tableWidget_2, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(PatientInfo);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        label_2 = new QLabel(PatientInfo);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        tableWidget = new QTableWidget(PatientInfo);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem8);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setLayoutDirection(Qt::LeftToRight);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setCornerButtonEnabled(false);

        gridLayout->addWidget(tableWidget, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        comboBox = new QComboBox(PatientInfo);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer_3 = new QSpacerItem(15, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_2 = new QPushButton(PatientInfo);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 1);


        retranslateUi(PatientInfo);

        QMetaObject::connectSlotsByName(PatientInfo);
    } // setupUi

    void retranslateUi(QWidget *PatientInfo)
    {
        PatientInfo->setWindowTitle(QCoreApplication::translate("PatientInfo", "Form", nullptr));
        label->setText(QCoreApplication::translate("PatientInfo", "\353\214\200\352\270\260 \355\231\230\354\236\220 \353\246\254\354\212\244\355\212\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PatientInfo", "\355\231\230\354\236\220 ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PatientInfo", "\355\231\230\354\236\220 \354\235\264\353\246\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PatientInfo", "\354\247\204\353\243\214 \355\230\204\355\231\251", nullptr));
        pushButton->setText(QCoreApplication::translate("PatientInfo", "\354\247\204\353\243\214\n"
"\354\213\234\354\236\221", nullptr));
        label_2->setText(QCoreApplication::translate("PatientInfo", "\355\231\230\354\236\220 \354\240\225\353\263\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PatientInfo", "\354\240\225\353\263\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PatientInfo", "\355\231\230\354\236\220 \353\262\210\355\230\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PatientInfo", "\355\231\230\354\236\220 \354\235\264\353\246\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PatientInfo", "\354\204\261\353\263\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PatientInfo", "\354\203\235\353\205\204\354\233\224\354\235\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PatientInfo", "\353\251\224\353\252\250", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("PatientInfo", "Ceph", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("PatientInfo", "Pano", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("PatientInfo", "Both", nullptr));

        pushButton_2->setText(QCoreApplication::translate("PatientInfo", "\354\264\254\354\230\201\n"
"\354\213\234\354\236\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientInfo: public Ui_PatientInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTINFO_H
