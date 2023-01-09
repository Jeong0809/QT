#include <QSplitter>
#include <QListWidget>
#include <QDir>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QColorDialog>

#include "imagealbum.h"
#include "ui_imagealbum.h"
#include "imageview.h"

#define LIMIT_UBYTE(n) (n > UCHAR_MAX) ? UCHAR_MAX:(n<0) ? 0 : n

ImageAlbum::ImageAlbum(QWidget *parent)
    : QSplitter(parent), ui(new Ui::ImageAlbum)
{
    imageView = new ImageView(this);
    imageView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    imageView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->setSceneRect(0, 0,
                                           imageView->graphicsScene->width(), imageView->graphicsScene->height());
    imageView->grabGesture(Qt::PinchGesture);

    listWidget = new QListWidget(this);
    listWidget->setViewMode(QListWidget::IconMode);
    listWidget->setIconSize(QSize(120, 80));
    listWidget->setResizeMode(QListWidget::Adjust);
    listWidget->setFlow(QListWidget::TopToBottom);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(selectItem(QListWidgetItem*)));


    setOrientation(Qt::Horizontal);
    addWidget(listWidget);
    addWidget(imageView);
    //    setStretchFactor(0, 3);

    QList<int> list;
    list << 520 << 100;
    setSizes(list);

    reloadImages();

    ui->setupUi(this);

    connect(ui->ZoomIn, SIGNAL(clicked()), this, SLOT(ZoomIn()));
    connect(ui->ZoomOut, SIGNAL(clicked()), this, SLOT(ZoomOut()));
    connect(ui->LeftRotate, SIGNAL(clicked()), this, SLOT(LeftRotate()));
    connect(ui->RightRotate, SIGNAL(clicked()), this, SLOT(RightRotate()));
    connect(ui->Brush, SIGNAL(clicked()), this, SLOT(Brush()));
    connect(ui->OrigImage, SIGNAL(clicked()), this, SLOT(OrigImage()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(Brightness(int)));
    connect(ui->Gamma, SIGNAL(clicked()), this, SLOT(Gamma()));
    connect(ui->Sobel, SIGNAL(clicked()), this, SLOT(Sobel()));
}

ImageAlbum::~ImageAlbum()
{

}

void ImageAlbum::reloadImages()
{
    QDir dir(".");
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp";
    QFileInfoList fileInfoList = dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
    imageView->graphicsScene->clear();

    listWidget->clear();
    for(int i = 0; i < fileInfoList.count(); i++) {
        QListWidgetItem* item = new QListWidgetItem(QIcon(fileInfoList.at(i).fileName()), NULL, listWidget); //, QListWidgetItem::UserType);
        item->setStatusTip(fileInfoList.at(i).fileName());
        listWidget->addItem(item);
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
    imageView->graphicsScene->addPixmap(QPixmap(origImage->statusTip()).scaled(640, 480,
                                                                               Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::selectItem(QListWidgetItem* item)
{
    origImage = item;
    imageView->resetTransform();
    imageView->graphicsScene->clear();
    imageView->graphicsScene->addPixmap(QPixmap(item->statusTip()).scaled(640, 480,
                                                                          Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageAlbum::setImage(QString path)
{
    imageView->resetTransform();
    imageView->graphicsScene->clear();
    imageView->graphicsScene->addPixmap(QPixmap(path).scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QFileInfo fileInfo(path);
    for(int i = 0; i < listWidget->count(); i++) {
        if(listWidget->item(i)->statusTip() == fileInfo.fileName()) {
            listWidget->setCurrentRow(i);
            break;
        }
    }

}

QString ImageAlbum::currentImage()
{
    return (listWidget->currentRow() >=0) ? listWidget->currentItem()->statusTip() : "";
}

void ImageAlbum::reset()
{
    imageView->resetTransform();
}

void ImageAlbum::Brightness(int value)
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(listWidget->currentItem()->statusTip());;

    for(int x = 0; x < image->width(); ++x)
        for(int y = 0 ; y < image->height(); ++y) {
            const QRgb rgb = image->pixel(x, y);
            const double r = LIMIT_UBYTE(qRed(rgb) + value);
            const double g = LIMIT_UBYTE(qGreen(rgb) + value);
            const double b = LIMIT_UBYTE(qBlue(rgb) + value);
            image->setPixelColor(x, y,
                                 QColor(
                                     r,
                                     g,
                                     b));
        }

    //    QSize size = image->size();
    //    image->scaled(size);

    QPixmap buf = QPixmap::fromImage(*image);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf);
}

void ImageAlbum::Gamma()
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(listWidget->currentItem()->statusTip());

    for(int x = 0; x < image->width(); ++x)
        for(int y = 0 ; y < image->height(); ++y) {
            const QRgb rgb = image->pixel(x, y);
            const double r = qRed(rgb) / 255.0;
            const double g = qGreen(rgb) / 255.0;
            const double b = qBlue(rgb) / 255.0;
            image->setPixelColor(x, y,
                                 QColor(
                                     255 * std::pow(r, 1.3),
                                     255 * std::pow(g, 1.3),
                                     255 * std::pow(b, 1.3)));
        }

    QPixmap buf = QPixmap::fromImage(*image);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf);
}

void ImageAlbum::Sobel()
{
    imageView->graphicsScene->clear();
    QImage *image = new QImage(listWidget->currentItem()->statusTip());
    QImage *out = image;

    int kx[3][3] = {{-1, 0 , 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int ky[3][3] = {{1, 2, 1},
                    {0, 0, 0},
                    {-1, -2, -1}};


    for(int y=1; y < image->height()-1; y++){
        for(int x = 1; x<image->width()-1; x++){

            int a = (QColor(image->pixel(x-1,y-1)).red() + QColor(image->pixel(x-1,y-1)).blue()
                     + QColor(image->pixel(x-1,y-1)).green())/3;
            int b = (QColor(image->pixel(x,y-1)).red() + QColor(image->pixel(x,y-1)).blue()
                     + QColor(image->pixel(x,y-1)).green())/3;
            int c = (QColor(image->pixel(x+1,y-1)).red() + QColor(image->pixel(x+1,y-1)).green()
                     + QColor(image->pixel(x+1,y-1)).blue())/3;
            int d = (QColor(image->pixel(x-1,y)).blue() + QColor(image->pixel(x-1,y)).green()
                     + QColor(image->pixel(x-1,y)).red())/3;
            int e = (QColor(image->pixel(x,y)).green() + QColor(image->pixel(x,y)).red() + QColor(image->pixel(x,y)).blue())/3;
            int f = (QColor(image->pixel(x+1,y)).blue() + QColor(image->pixel(x+1,y)).red()
                     + QColor(image->pixel(x+1,y)).green())/3;
            int g = (QColor(image->pixel(x-1,y+1)).green() + QColor(image->pixel(x-1,y+1)).red()
                     + QColor(image->pixel(x-1,y+1)).blue())/3;
            int h = (QColor(image->pixel(x,y+1)).blue() + QColor(image->pixel(x,y+1)).green()
                     + QColor(image->pixel(x,y+1)).red())/3;
            int i = (QColor(image->pixel(x+1,y+1)).red() + QColor(image->pixel(x+1,y+1)).green()
                     + QColor(image->pixel(x+1,y+1)).blue())/3;

            int matrix[3][3] = {{a,b,c},
                                {d,e,f},
                                {g,h,i}};
            int sumx = 0;
            int sumy = 0;

            for(int s=0; s<3; s++){
                for(int t=0; t<3; t++){
                    sumx = sumx + (matrix[s][t] * kx[s][t]);
                    sumy = sumy + (matrix[s][t] * ky[s][t]); /* use ky, not kx */
                }
            }

            int newValue = sqrt(pow(sumx, 2) + pow(sumy, 2));

            /* omitted, same as the original code */

            QColor test = QColor(image->pixel(x,y));

            test.setRed(newValue);
            test.setBlue(newValue);
            test.setGreen(newValue);

            out->setPixel(x, y, test.rgb()); /* modify out, not img */
        }
    }

    image = out; /* filter calculation is done, so update img */

    QPixmap buf = QPixmap::fromImage(*image);
    imageView->setScene(imageView->graphicsScene);
    imageView->graphicsScene->addPixmap(buf);
}

