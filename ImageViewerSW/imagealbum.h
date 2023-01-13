#ifndef IMAGEALBUM_H
#define IMAGEALBUM_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

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
    QListWidget* listWidget;
    QGroupBox* groupBox;
    ImageView* imageView;
    QListWidgetItem* origImage;
    QColor paintColor;
    QImage *selectImage;


    bool _pan;
    int _panStartX, _panStartY;
    int _numScheduledScalings;
    int _currentStepScaleFactor;
    int _scaleFactor, _rotationAngle;
    QPixmap buf;

    void filter(Mat img, Mat& dst, Mat mask);

public slots:
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
    void Reverse();
    void HistEqual();
    void Sharpening();
};

#endif // IMAGEALBUM_H

