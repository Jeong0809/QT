/********************************************************************************
** Form generated from reading UI file 'imagealbum.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEALBUM_H
#define UI_IMAGEALBUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageAlbum
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QToolButton *ZoomIn;
    QToolButton *ZoomOut;
    QToolButton *LeftRotate;
    QToolButton *RightRotate;
    QToolButton *Sharpening;
    QToolButton *HistEqual;
    QToolButton *OrigImage;
    QToolButton *Brush;
    QToolButton *Sobel;
    QToolButton *VReverse;
    QToolButton *HReverse;
    QToolButton *Blur;
    QToolButton *Reverse;
    QLabel *label;
    QSlider *horizontalSlider;
    QLabel *label_2;
    QDoubleSpinBox *Contrast;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ImageAlbum)
    {
        if (ImageAlbum->objectName().isEmpty())
            ImageAlbum->setObjectName("ImageAlbum");
        ImageAlbum->resize(890, 557);
        ImageAlbum->setCursor(QCursor(Qt::ArrowCursor));
        ImageAlbum->setMouseTracking(false);
        ImageAlbum->setFocusPolicy(Qt::NoFocus);
        gridLayout_2 = new QGridLayout(ImageAlbum);
        gridLayout_2->setObjectName("gridLayout_2");
        splitter = new QSplitter(ImageAlbum);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(300, 16777215));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        ZoomIn = new QToolButton(groupBox);
        ZoomIn->setObjectName("ZoomIn");

        formLayout->setWidget(0, QFormLayout::LabelRole, ZoomIn);

        ZoomOut = new QToolButton(groupBox);
        ZoomOut->setObjectName("ZoomOut");

        formLayout->setWidget(0, QFormLayout::FieldRole, ZoomOut);

        LeftRotate = new QToolButton(groupBox);
        LeftRotate->setObjectName("LeftRotate");

        formLayout->setWidget(1, QFormLayout::LabelRole, LeftRotate);

        RightRotate = new QToolButton(groupBox);
        RightRotate->setObjectName("RightRotate");

        formLayout->setWidget(1, QFormLayout::FieldRole, RightRotate);

        Sharpening = new QToolButton(groupBox);
        Sharpening->setObjectName("Sharpening");

        formLayout->setWidget(2, QFormLayout::LabelRole, Sharpening);

        HistEqual = new QToolButton(groupBox);
        HistEqual->setObjectName("HistEqual");

        formLayout->setWidget(2, QFormLayout::FieldRole, HistEqual);

        OrigImage = new QToolButton(groupBox);
        OrigImage->setObjectName("OrigImage");

        formLayout->setWidget(3, QFormLayout::LabelRole, OrigImage);

        Brush = new QToolButton(groupBox);
        Brush->setObjectName("Brush");

        formLayout->setWidget(3, QFormLayout::FieldRole, Brush);

        Sobel = new QToolButton(groupBox);
        Sobel->setObjectName("Sobel");

        formLayout->setWidget(4, QFormLayout::FieldRole, Sobel);

        VReverse = new QToolButton(groupBox);
        VReverse->setObjectName("VReverse");

        formLayout->setWidget(5, QFormLayout::LabelRole, VReverse);

        HReverse = new QToolButton(groupBox);
        HReverse->setObjectName("HReverse");

        formLayout->setWidget(5, QFormLayout::FieldRole, HReverse);

        Blur = new QToolButton(groupBox);
        Blur->setObjectName("Blur");

        formLayout->setWidget(6, QFormLayout::LabelRole, Blur);

        Reverse = new QToolButton(groupBox);
        Reverse->setObjectName("Reverse");

        formLayout->setWidget(6, QFormLayout::FieldRole, Reverse);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(7, QFormLayout::LabelRole, label);

        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMinimum(-20);
        horizontalSlider->setMaximum(20);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);

        formLayout->setWidget(7, QFormLayout::FieldRole, horizontalSlider);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        formLayout->setWidget(8, QFormLayout::LabelRole, label_2);

        Contrast = new QDoubleSpinBox(groupBox);
        Contrast->setObjectName("Contrast");
        Contrast->setMaximum(5.000000000000000);
        Contrast->setSingleStep(0.200000000000000);
        Contrast->setValue(1.000000000000000);

        formLayout->setWidget(8, QFormLayout::FieldRole, Contrast);

        splitter->addWidget(groupBox);

        gridLayout_2->addWidget(splitter, 0, 1, 1, 1);

        listWidget = new QListWidget(ImageAlbum);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(600, 100));
        listWidget->setMaximumSize(QSize(1000, 100));
        listWidget->setBaseSize(QSize(600, 80));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setIconSize(QSize(120, 80));
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setResizeMode(QListView::Adjust);
        listWidget->setViewMode(QListView::IconMode);

        gridLayout_2->addWidget(listWidget, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton = new QPushButton(ImageAlbum);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(ImageAlbum);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {background-color: rgb(224, 255, 114)}"));

        horizontalLayout_2->addWidget(pushButton_2);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 1, 1, 1);

#if QT_CONFIG(shortcut)
        label->setBuddy(horizontalSlider);
        label_2->setBuddy(Contrast);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ImageAlbum);

        QMetaObject::connectSlotsByName(ImageAlbum);
    } // setupUi

    void retranslateUi(QWidget *ImageAlbum)
    {
        ImageAlbum->setWindowTitle(QCoreApplication::translate("ImageAlbum", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ImageAlbum", "GroupBox", nullptr));
        ZoomIn->setText(QCoreApplication::translate("ImageAlbum", "\354\244\214\354\235\270", nullptr));
        ZoomOut->setText(QCoreApplication::translate("ImageAlbum", "\354\244\214\354\225\204\354\233\203", nullptr));
        LeftRotate->setText(QCoreApplication::translate("ImageAlbum", "\354\242\214\355\232\214\354\240\204", nullptr));
        RightRotate->setText(QCoreApplication::translate("ImageAlbum", "\354\232\260\355\232\214\354\240\204", nullptr));
        Sharpening->setText(QCoreApplication::translate("ImageAlbum", "\354\203\244\355\224\204\353\213\235", nullptr));
        HistEqual->setText(QCoreApplication::translate("ImageAlbum", "\355\236\210\354\212\244\355\206\240\352\267\270\353\236\250 \355\217\211\355\231\234\355\231\224", nullptr));
        OrigImage->setText(QCoreApplication::translate("ImageAlbum", "\354\233\220\353\263\270", nullptr));
        Brush->setText(QCoreApplication::translate("ImageAlbum", "\353\270\214\353\237\254\354\211\254", nullptr));
        Sobel->setText(QCoreApplication::translate("ImageAlbum", "\354\206\214\353\262\250", nullptr));
        VReverse->setText(QCoreApplication::translate("ImageAlbum", "\354\242\214\354\232\260 \353\260\230\354\240\204", nullptr));
        HReverse->setText(QCoreApplication::translate("ImageAlbum", "\354\203\201\355\225\230 \353\260\230\354\240\204", nullptr));
        Blur->setText(QCoreApplication::translate("ImageAlbum", "\353\270\224\353\237\254", nullptr));
        Reverse->setText(QCoreApplication::translate("ImageAlbum", "\353\260\230\354\240\204", nullptr));
        label->setText(QCoreApplication::translate("ImageAlbum", "\353\260\235\352\270\260", nullptr));
        label_2->setText(QCoreApplication::translate("ImageAlbum", "\353\214\200\353\271\204", nullptr));
        pushButton->setText(QCoreApplication::translate("ImageAlbum", "\354\262\230\353\260\251\354\240\204\n"
"\354\236\221\354\204\261", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ImageAlbum", "\354\247\204\353\243\214\n"
"\354\242\205\353\243\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageAlbum: public Ui_ImageAlbum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEALBUM_H
