#include "editimage.h"
#include "ui_editimage.h"

EditImage::EditImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditImage)
{

}

EditImage::~EditImage()
{
    delete ui;
}

void EditImage::openImage()
{
    qDebug() << "JH";
//    ui->setupUi(this);
}
