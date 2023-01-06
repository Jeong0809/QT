#include "widget.h"
#include "ui_widget.h"
#include "brush.h"

#define RADIUS      5

class OhBrush;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    paintColor = Qt::black;

    ohBrush = new OhBrush();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
    connect(ui->ZoomIn, SIGNAL(clicked()), this, SLOT(ZoomIn()));
    connect(ui->ZoomOut, SIGNAL(clicked()), this, SLOT(ZoomOut()));
    connect(ui->LeftRotate, SIGNAL(clicked()), this, SLOT(LeftRotate()));
    connect(ui->RightRotate, SIGNAL(clicked()), this, SLOT(RightRotate()));
    connect(ui->Brush, SIGNAL(clicked()), this, SLOT(Brush()));
    connect(ui->Hand, SIGNAL(clicked()), this, SLOT(Hand()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::ButtonClicked()
{
    QFileDialog dlg;
    QString filePath = dlg.getOpenFileName(this, "Load Image", "", "Image Files (*.png *.jpg *.bmp)");
    //    QString fileName = filePath.section("/", -1);
    img = new QImage(filePath);

    /*QPixmap*/ buf = QPixmap::fromImage(*img);
    buf = buf.scaled(img->width(), img->height());

//    scene = new QGraphicsScene(ohBrush);
    /*QGraphicsScene* */scene = new QGraphicsScene;

    ui->graphicsView->setScene(scene);
    scene->addPixmap(buf);

}

void Widget::Hand()
{
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void Widget::Brush()
{

    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    paintColor = QColorDialog::getColor(paintColor, this);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    // When you press the mouse button, draw the ellipse
    scene->addEllipse(event->pos().x(),
                      event->pos().y(),
                      30,
                      30,
                      QPen(Qt::NoPen),
                      QBrush(paintColor));
    qDebug("%d", event->pos().x());
    qDebug("%d", event->pos().y());
    // Save the coordinates of the point of pressing
    previousPoint = event->pos();
}

void Widget::LeftRotate()
{
    ui->graphicsView->rotate(-45);
}

void Widget::RightRotate()
{
    ui->graphicsView->rotate(45);
}

void Widget::ZoomIn()
{
    ui->graphicsView->scale(1.2, 1.2);
}

void Widget::ZoomOut()
{
    ui->graphicsView->scale(0.8, 0.8);
}


//void Widget::mouseMoveEvent(QMouseEvent *event)
//{
//    // We draw the line with the previous coordinates
////    scene->addLine(previousPoint.x(),
////            previousPoint.y(),
////            event->pos().x(),
////            event->pos().y(),
////            QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
////    // Update on the previous coordinate data
////    previousPoint = event->pos();

//    scene->addLine(event->pos().x(),
//            event->pos().x(),
//            event->pos().x()+2,
//            event->pos().y()+2,
//            QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
//    // Update on the previous coordinate data
//    previousPoint = event->pos();

//    scene->addLine(5,
//            5,
//            20,
//            20,
//            QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
//}

