/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionText;
    QAction *actionCut;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frame;
    QFrame *frame_2;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(879, 600);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionText = new QAction(MainWindow);
        actionText->setObjectName("actionText");
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(320, 16777215));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 0, 0, 1, 1);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame_2, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 879, 17));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionAbout);
        toolBar->addAction(actionText);
        toolBar->addSeparator();
        toolBar->addAction(actionCut);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\353\217\204\354\233\200\353\247\220", nullptr));
        actionText->setText(QCoreApplication::translate("MainWindow", "\355\205\215\354\212\244\355\212\270", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "\354\236\220\353\245\264\352\270\260", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\353\217\204\354\233\200\353\247\220", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
