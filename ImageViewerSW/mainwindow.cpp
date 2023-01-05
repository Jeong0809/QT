#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editimage.h"

#include <QFileDialog>
#include <QColorSpace>
#include <QMessageBox>
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    editimage = new EditImage(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
    connect(ui->actionzoomIn, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
    connect(ui->actionzoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));

    connect(ui->graphicsView, SIGNAL(popUpImage()),
            editimage, SLOT(openImage()));

    connect(this, SIGNAL(popUpImage()),
                editimage, SLOT(openImage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonClicked()
{
    QFileDialog dlg;
    QString filePath = dlg.getOpenFileName(this, "Load Image", "", "Image Files (*.png *.jpg *.bmp)");
    QString fileName = filePath.section("/", -1);
    QImage *img = new QImage(filePath);

    QSize size = img->size();
    img->scaled(size);

    QPixmap buf = QPixmap::fromImage(*img);
    buf = buf.scaled(ui->graphicsView->width(), ui->graphicsView->height());

    QGraphicsScene* scene = new QGraphicsScene;

    ui->graphicsView->setScene(scene);
    scene->addPixmap(buf);
}

void MainWindow::zoomIn()
{
//    img.scaled();
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
//    setTransformationAnchor(AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);
//    double scalefactor = 1.5;
//    if(event->delta() > 0)
//    {
//        scale(scalefactor, scalefactor);
//    }

//    else {
//        scale(1/scalefactor, 1/scalefactor);
//    }
}



void MainWindow::on_graphicsView_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << "1";
    emit popUpImage();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    qDebug() << "2";
    emit popUpImage();
}


void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{
    qDebug() << "3";
    emit popUpImage();
}

