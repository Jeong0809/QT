#include "patientinfo.h"
#include "ui_patientinfo.h"

PatientInfo::PatientInfo(QWidget *parent) :
    QWidget(parent), ui(new Ui::PatientInfo)
{
    ui->setupUi(this);
}

PatientInfo::~PatientInfo()
{
    delete ui;
}

void PatientInfo::receiveWaitingList(QString ID, QString Name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem;
    ui->WaitingList->addTopLevelItem(item);
    item->setText(0, ID);
    item->setText(1, Name);
    item->setText(2, "대기중");
}

void PatientInfo::on_WaitingList_itemClicked(QTreeWidgetItem *item, int column)
{
    selectPatientID = item->text(0);
    qDebug() << item->text(0);
}


void PatientInfo::on_pushButton_clicked()
{
    qDebug() << "진료 시작";
    QString Data = "VTS<CR>" + selectPatientID + "<CR>" + "";
    emit sendPatientInfo(Data);
}

