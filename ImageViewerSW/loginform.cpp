#include "loginform.h"
#include "ui_loginform.h"

#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::receiveLogInCheck(QString data)
{
    Check = data;
}

void LoginForm::on_LogIn_clicked()
{
    QString DoctorID = ui->DoctorID->text();
    QString DoctorName = ui->DoctorName->text();

    if(DoctorID == "" || DoctorName == "")
    {
        QMessageBox:: critical(this, "경고",
                              "아이디/이름을 입력하세요");
    }

    QString Data = "VLG<CR>" + DoctorID + "<CR>" + DoctorName;

    emit SendDoctorCheck(Data);


}

