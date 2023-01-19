#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <QWidget>

namespace Ui {
class Prescription;
}

class Prescription : public QWidget
{
    Q_OBJECT

public:
    explicit Prescription(QWidget *parent = nullptr);
    ~Prescription();

private:
    Ui::Prescription *ui;
};

#endif // PRESCRIPTION_H
