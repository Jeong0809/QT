#ifndef PATIENTINFO_H
#define PATIENTINFO_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class PatientInfo;
}

class PatientInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PatientInfo(QWidget *parent = nullptr);
    ~PatientInfo();

private:
    Ui::PatientInfo *ui;
//    QTreeWidgetItem* selectPatient;
    QString selectPatientID;

private slots:
    void receiveWaitingList(QString, QString);
    void on_WaitingList_itemClicked(QTreeWidgetItem *item, int column);
    void on_pushButton_clicked();

signals:
    void sendPatientInfo(QString);
};

#endif // PATIENTINFO_H
