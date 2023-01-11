#ifndef IMAGEALBUM_H
#define IMAGEALBUM_H

#include <QWidget>
#include <QSplitter>
#include <QGraphicsSceneMouseEvent>

class ImageView;
class QGraphicsScene;
class QListWidget;
class QListWidgetItem;
class QGroupBox;

namespace Ui {
class ImageAlbum;
}

class ImageAlbum : public QWidget
{
    Q_OBJECT

public:
    explicit ImageAlbum(QWidget *parent = nullptr);
    ~ImageAlbum();
    QString currentImage();

private:
    Ui::ImageAlbum *ui;
    QGraphicsScene* graphicsScene;
    QListWidget* listWidget;
    QGroupBox* groupBox;
    ImageView* imageView;
    QListWidgetItem* origImage;
    QColor paintColor;
    QImage *selectImage;

public slots:
    void reset();
    void reloadImages();
    void selectItem(QListWidgetItem*);
    void setImage(QString);
    void ZoomIn();
    void ZoomOut();
    void LeftRotate();
    void RightRotate();
    void Brush();
    void OrigImage();
    void Contrast(double value);
    void Brightness(int value);
    void Sobel();
    void VReverse();
    void HReverse();
    void Blur();
    void Edge();
    void Reverse();
};

#endif // IMAGEALBUM_H

