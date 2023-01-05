#ifndef EDITIMAGE_H
#define EDITIMAGE_H

#include <QWidget>
#include <QGraphicsView>

namespace Ui {
class EditImage;
}

class EditImage : public QWidget
{
    Q_OBJECT

public:
    explicit EditImage(QWidget *parent = nullptr);
    ~EditImage();

private:
    Ui::EditImage *ui;

public slots:
    void openImage();

};

#endif // EDITIMAGE_H
