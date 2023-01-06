#ifndef WIDGET_H
#define WIDGET_H

#include "qgraphicsview.h"
#include <QWidget>
#include <QFileDialog>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class OhBrush;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QImage *img;
    QPixmap buf;
    QColor paintColor;
    QGraphicsScene* scene;
    QPointF     previousPoint;
    OhBrush* ohBrush;

    bool modified;
    QPointF prevPos;
    qreal  paintSize;
    QGraphicsSceneMouseEvent *event;
    virtual void mousePressEvent(QMouseEvent *event);


signals:
    void sendBrush(OhBrush*, QColor);


private slots:
    void ButtonClicked();
    void ZoomIn();
    void ZoomOut();
    void LeftRotate();
    void RightRotate();
    void Brush();
    void Hand();
};
#endif // WIDGET_H
