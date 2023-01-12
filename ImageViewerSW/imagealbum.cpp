#include <QSplitter>
#include <QListWidget>
#include <QDir>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QColorDialog>
#include <QMouseEvent>
#include <QMessageBox>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

#include "imagealbum.h"
#include "ui_imagealbum.h"
#include "imageview.h"

#define LIMIT_UBYTE(n) (n > UCHAR_MAX) ? UCHAR_MAX:(n<0) ? 0 : n

ImageAlbum::ImageAlbum(QWidget *parent)
    : QWidget(parent), ui(new Ui::ImageAlbum)
{
    ui->setupUi(this);

    imageView = new ImageView(this);
    imageView->setGeometry(6, 6, 600, 600);
    imageView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    imageView->setDragMode(QGraphicsView::NoDrag);


    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(selectItem(QListWidgetItem*)));

    connect(ui->ZoomIn, SIGNAL(clicked()), this, SLOT(ZoomIn()));
    connect(ui->ZoomOut, SIGNAL(clicked()), this, SLOT(ZoomOut()));
    connect(ui->LeftRotate, SIGNAL(clicked()), this, SLOT(LeftRotate()));
    connect(ui->RightRotate, SIGNAL(clicked()), this, SLOT(RightRotate()));
    connect(ui->Brush, SIGNAL(clicked()), this, SLOT(Brush()));
    connect(ui->OrigImage, SIGNAL(clicked()), this, SLOT(OrigImage()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(Brightness(int)));
    connect(ui->Sobel, SIGNAL(clicked()), this, SLOT(Sobel()));
    connect(ui->VReverse, SIGNAL(clicked()), this, SLOT(VReverse()));
    connect(ui->HReverse, SIGNAL(clicked()), this, SLOT(HReverse()));
    connect(ui->Blur, SIGNAL(clicked()), this, SLOT(Blur()));
    connect(ui->Reverse, SIGNAL(clicked()), this, SLOT(Reverse()));
    connect(ui->Contrast, SIGNAL(valueChanged(double)), this, SLOT(Contrast(double)));
    connect(ui->HistEqual, SIGNAL(clicked()), this, SLOT(HistEqual()));
    connect(ui->Sharpening, SIGNAL(clicked()), this, SLOT(Sharpening()));

    reloadImages();
}

ImageAlbum::~ImageAlbum()
{

}

void ImageAlbum::reloadImages()
{
    QDir dir(".");
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp" << "*.gif";
    QFileInfoList fileInfoList = dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
    imageView->graphicsScene->clear();

    ui->listWidget->clear();
    for(int i = 0; i < fileInfoList.count(); i++) {
        QListWidgetItem* item = new QListWidgetItem(QIcon(fileInfoList.at(i).fileName()), NULL, ui->listWidget); //, QListWidgetItem::UserType);
        item->setStatusTip(fileInfoList.at(i).fileName());
        ui->listWidget->addItem(item);
    };
}

void ImageAlbum::Brush()
{
    imageView->setDragMode(QGraphicsView::NoDrag);
    paintColor = QColorDialog::getColor(paintColor, this);
}

void ImageAlbum::ZoomIn()
{
    imageView->scale(1.2, 1.2);
}

void ImageAlbum::ZoomOut()
{
    imageView->scale(0.8, 0.8);
}

void ImageAlbum::LeftRotate()
{
    imageView->rotate(-45);
}

void ImageAlbum::RightRotate()
{
    imageView->rotate(45);
}

void ImageAlbum::OrigImage()
{
    imageView->resetTransform();
    imageView->graphicsScene->clear();
    imageView->graphicsScene->addPixmap(QPixmap(origImage->statusTip()).scaled(imageView->width(), imageView->height(),
                                                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::selectItem(QListWidgetItem* item)
{
    origImage = item;
    selectImage = new QImage(ui->listWidget->currentItem()->statusTip());
    imageView->resetTransform();
    imageView->graphicsScene->clear();
    imageView->graphicsScene->addPixmap(QPixmap(item->statusTip()).scaled(imageView->width(), imageView->height(),
    Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    qDebug() << selectImage->width();
}

void ImageAlbum::setImage(QString path)
{
    imageView->resetTransform();
    imageView->graphicsScene->clear();
    imageView->graphicsScene->addPixmap(QPixmap(path).scaled(imageView->width(), imageView->height(),
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QFileInfo fileInfo(path);
    for(int i = 0; i < ui->listWidget->count(); i++) {
        if(ui->listWidget->item(i)->statusTip() == fileInfo.fileName()) {
            ui->listWidget->setCurrentRow(i);
            break;
        }
    }
}

QString ImageAlbum::currentImage()
{
    return (ui->listWidget->currentRow() >=0) ? ui->listWidget->currentItem()->statusTip() : "";
}

void ImageAlbum::reset()
{
    imageView->resetTransform();
}

void ImageAlbum::VReverse()
{
    imageView->graphicsScene->clear();
    selectImage->mirror(true, false);

    QPixmap buf = QPixmap::fromImage(*selectImage);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::HReverse()
{
    imageView->graphicsScene->clear();
    selectImage->mirror(false, true);

    QPixmap buf = QPixmap::fromImage(*selectImage);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::Brightness(int value)
{
    imageView->graphicsScene->clear();
    QImage *image = selectImage;
//    QImage* image = nullptr;
    *image = image->convertToFormat(QImage::Format_RGB888);
//    image = selectImage->convertToFormat(QImage::Format_RGB32);

    cv::Mat in = cv::Mat(
                image->height(),
                image->width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine());
    Mat out;
    cvtColor(in, out, cv::COLOR_BGR2GRAY);
    out = out + value;

    QImage image_brightness(
                out.data,
                out.cols,
                out.rows,
                out.step,
                QImage::Format_Grayscale8);
//    selectImage = &image_brightness;

    QPixmap buf = QPixmap::fromImage(image_brightness);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::HistEqual()
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(ui->listWidget->currentItem()->statusTip());

    *image = image->convertToFormat(QImage::Format_RGB888);
    cv::Mat in = cv::Mat(
                image->height(),
                image->width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine());
    Mat out, Hist;
    cvtColor(in, out, cv::COLOR_BGR2GRAY);
    equalizeHist(out, Hist);

    QImage image_Histogram(
                Hist.data,
                Hist.cols,
                Hist.rows,
                Hist.step,
                QImage::Format_Grayscale8);

    QPixmap buf = QPixmap::fromImage(image_Histogram);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::Reverse()
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(ui->listWidget->currentItem()->statusTip());

    *image = image->convertToFormat(QImage::Format_RGB888);
    cv::Mat in = cv::Mat(
                image->height(),
                image->width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine());
    Mat out;
    cvtColor(in, out, cv::COLOR_BGR2GRAY);
    out = 255 - out;

    QImage image_brightness(
                out.data,
                out.cols,
                out.rows,
                out.step,
                QImage::Format_Grayscale8);

    QPixmap buf = QPixmap::fromImage(image_brightness);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::Contrast(double value)
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(ui->listWidget->currentItem()->statusTip());

    *image = image->convertToFormat(QImage::Format_RGB888);
    cv::Mat in = cv::Mat(
                image->height(),
                image->width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine());
    Mat out;
    cvtColor(in, out, cv::COLOR_BGR2GRAY);
    out = out * value ;

    QImage image_contrast(
                out.data,
                out.cols,
                out.rows,
                out.step,
                QImage::Format_Grayscale8);

    QPixmap buf = QPixmap::fromImage(image_contrast);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::Sobel()
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(ui->listWidget->currentItem()->statusTip());

    int scale = 1;
    int delta = 0;
    int ddepth = CV_32FC1;

    *image = image->convertToFormat(QImage::Format_RGB888);
    Mat in = cv::Mat(
                image->height(),
                image->width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine());

    Mat out, grad_x, grad_y;

    //color->gray로 컬러 변환
    cvtColor(in, out, cv::COLOR_BGR2GRAY);
    cv::Sobel(out, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_CONSTANT);
    cv::Sobel(out, grad_y, ddepth, 1, 0, 3, scale, delta, cv::BORDER_CONSTANT);

    Mat float_mag, mag;
    magnitude(grad_x, grad_y, float_mag);
    float_mag.convertTo(mag, CV_8UC1);

    QImage image_sobel(
                mag.data,
                mag.cols,
                mag.rows,
                mag.step,
                QImage::Format_Grayscale8);

    QPixmap buf = QPixmap::fromImage(image_sobel);

    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::Blur()
{
    imageView->graphicsScene->clear();

    // 이미지를 불러왔는지 확인합니다.
    if (imageView->graphicsScene == nullptr) {
        QMessageBox::information(this, "Information", "No image to edit.");
        return;
    }

    QImage *image = new QImage(ui->listWidget->currentItem()->statusTip());

    //OpenCV에서 이미지 작업을 하기 위해서 Matrix 타입으로 만들기 위해서 이미지 변환 작업을 해줍니다.
    *image = image->convertToFormat(QImage::Format_RGB888);
    cv::Mat mat = cv::Mat(
                image->height(),
                image->width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine());

    // OpenCV에 있는 blur() 함수를 실행합니다. imgproc 모듈 안에 있는 기능입니다.
    // 첫 번째 인수는 원본 이미지, 두 번째 인수는 blur 된 이미지, 세 번째 인수는 커널의 크기입니다. 여기에서 커널은
    // OpenCV에게 주어진 픽셀의 값을 서로 다른 양의 인접 픽셀과 결합하여 값을 변경하는 방법을 알려줍니다.

    cv::Mat tmp;
    blur(mat, tmp, cv::Size(18, 18));
    mat = tmp;

    //다시 볼 수 있는 형태로 이미지를 복구시킵니다.
    QImage image_blurred(
                mat.data,
                mat.cols,
                mat.rows,
                mat.step,
                QImage::Format_RGB888);

    QPixmap buf = QPixmap::fromImage(image_blurred);

    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::filter(Mat img, Mat& dst, Mat mask)
{
    dst = Mat(img.size(), CV_32F, Scalar(0));

    Point h_m = mask.size() / 2;

    for(int i = h_m.y; i < img.rows - h_m.y; i++){
        for(int j = h_m.x; j < img.cols - h_m.x; j++){

            float sum = 0;
            for(int u = 0; u < mask.rows; u++){
                for(int v = 0; v < mask.cols; v++){
                    int y = i + u - h_m.y;
                    int x = j + v - h_m.x;
                    sum += mask.at<float>(u, v) * img.at<uchar>(y, x);
                }
            }
            dst.at<float>(i, j) = sum;
        }
    }
}

void ImageAlbum::Sharpening()
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(ui->listWidget->currentItem()->statusTip());

    //OpenCV에서 이미지 작업을 하기 위해서 Matrix 타입으로 만들기 위해서 이미지 변환 작업을 해줍니다.
    *image = image->convertToFormat(QImage::Format_RGB888);
    cv::Mat mat = cv::Mat(
                image->height(),
                image->width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine());

    Mat blurred, out;
    cvtColor(mat, out, cv::COLOR_BGR2GRAY);
    GaussianBlur(mat, blurred, Size(), 8);

    float alpha = 1.f;
    Mat dst = (1 + alpha) * mat - alpha * blurred;

    QImage image_sharpened(
                dst.data,
                dst.cols,
                dst.rows,
                dst.step,
                QImage::Format_RGB888);

    QPixmap buf = QPixmap::fromImage(image_sharpened);

    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf.scaled(imageView->width(), imageView->height(),
                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}







