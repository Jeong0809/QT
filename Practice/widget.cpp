#include "widget.h"
#include "ui_widget.h"

#define RADIUS      5

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    paintColor = Qt::black;
    scene = new QGraphicsScene;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
    connect(ui->ZoomIn, SIGNAL(clicked()), this, SLOT(ZoomIn()));
    connect(ui->ZoomOut, SIGNAL(clicked()), this, SLOT(ZoomOut()));
    connect(ui->LeftRotate, SIGNAL(clicked()), this, SLOT(LeftRotate()));
    connect(ui->RightRotate, SIGNAL(clicked()), this, SLOT(RightRotate()));
    connect(ui->Brush, SIGNAL(clicked()), this, SLOT(Brush()));

    //    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
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

    /*QGraphicsScene* */scene = new QGraphicsScene;
    //scene->setb
    ui->graphicsView->setScene(scene);
    scene->addPixmap(buf);

}

void Widget::Brush()
{
    paintColor = QColorDialog::getColor(paintColor, this);
//    scene->setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
//    scene->
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->scenePosition();
    qDebug() << event->position();
    qDebug() << event->pos();
    qDebug() << event->globalPosition();

    // When you press the mouse button, draw the ellipse
    scene->addEllipse(event->position().rx() - 5,
               event->position().ry() - 5,
               10,
               10,
               QPen(Qt::NoPen),
               QBrush(Qt::red));
    // Save the coordinates of the point of pressing
    previousPoint = event->pos();
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

void Widget::mouseMoveEvent(QMouseEvent *event)
 {
 }

 void Widget::mouseReleaseEvent(QMouseEvent *event)
 {
 }


//void Widget::mouseMoveEvent(QMouseEvent* event)
//{
//    QPointF newPos = event->pos();
//    if(modified) {
//        QPen pen(paintColor, paintSize);
//        pen.setCapStyle(Qt::RoundCap);
//        pen.setJoinStyle(Qt::RoundJoin);
//        QPainter painter(ui->graphicsView);
//        painter.setPen(pen);
//        painter.drawLine(prevPos, newPos);
//        painter.end();
//    }
//    int x1, x2, y1, y2;
//    if(prevPos.x() < newPos.x()) {
//        x1 = prevPos.x(); x2 = newPos.x();
//    } else {
//        x1 = newPos.x(); x2 = prevPos.x();
//    }

//    if(prevPos.y() < newPos.y()) {
//        y1 = prevPos.y(); y2 = newPos.y();
//    } else {
//        y1 = newPos.y(); y2 = prevPos.y();
//    }

//    QRectF rect(x1, y1, x2, y2);

//    update(rect.toRect().adjusted(-RADIUS, -RADIUS, +RADIUS, +RADIUS));
//    prevPos = newPos;
//}

//void Widget::mouseReleaseEvent(QMouseEvent* event)
//{
//    //    prevPos = event->pos();
//    QPen pen(paintColor, paintSize);
//    pen.setCapStyle(Qt::RoundCap);
//    QPainter painter(img);
//    painter.setPen(pen);
//    painter.drawPoint(prevPos);
//    painter.end();
//    modified = false;

//    update();
//}

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

