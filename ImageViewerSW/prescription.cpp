#include "prescription.h"
#include "ui_prescription.h"

Prescription::Prescription(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prescription)
{
    ui->setupUi(this);
}

Prescription::~Prescription()
{
    delete ui;
}
