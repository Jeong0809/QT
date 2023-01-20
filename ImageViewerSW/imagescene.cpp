#include "imagescene.h"

#include <QMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QTimeLine>
#include <QPinchGesture>
#include <QGraphicsItem>

#define ItemWidth   16

ImageScene::ImageScene(QWidget *parent)
    : QGraphicsScene(parent)
{

    QPainterPath path;
    m_pathItem = addPath(path);

    //펜의 색상, 두께의 초깃값 설정
    m_penColor = Qt::black;
    m_penThickness = 10;

//    resetTransform();
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

void ImageScene::ReceiveType(int type)
{
    m_drawType = Lines;
    qDebug() << "ImageView : " << m_drawType;
}

void ImageScene::ReceiveBrushColor(QColor paintColor)
{
    m_penColor = paintColor;
    qDebug() << "ImageView : " << m_penColor;
}

void ImageScene::ReceiveThickness(int Thickness)
{
    m_penThickness = Thickness;
    qDebug() << "ImageView : " << m_penThickness;
}

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mousePressEvent");
    if(items(event->scenePos()).isEmpty()) {
        if(m_drawType == Lines) {
            m_isDrawable = true;

            QPainterPath path;
            QGraphicsPathItem* item = addPath(path, QPen(Qt::NoPen), QBrush(m_penColor));

            path = item->path();
            path.moveTo(event->scenePos());
            item->setPath(path);

            m_pathList.append(item);
        }
//        else if(m_drawType != Cursor) {
//            m_startPos = event->scenePos();
//        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void ImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mouseReleaseEvent");
    Q_UNUSED(event);

//    if(m_currentItem != nullptr)
//        delete m_currentItem;

    switch (m_drawType) {
//    case Cursor:
//        break;
//    case Line:
//        addLineItem(m_startPos, mouseEvent->scenePos());
//        break;
//    case Rect:
//        addRectItem(m_startPos, mouseEvent->scenePos());
//        break;
//    case Ellipse:
//        addEllipseItem(m_startPos, mouseEvent->scenePos());
//        break;
    case Lines:
        if(m_isDrawable) {
            QGraphicsPathItem* item = m_pathList.last();
            if(item) {
                QPainterPath path = item->path();
                path.lineTo(event->scenePos());
                item->setPath(path);
                item->setFlag(QGraphicsItem::ItemIsMovable, true);
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            }
            m_isDrawable = false;
        }
        break;
//    case Image:
//        addImageItem(m_startPos, mouseEvent->scenePos());
//        break;
//    case Star:
//        addStarItem(m_startPos, mouseEvent->scenePos());
//        break;
//    }
//    m_currentItem = nullptr;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mouseMoveEvent");
    if(m_drawType == Lines) {
        if(m_isDrawable) {
            QGraphicsPathItem* item = m_pathList.last();
            if(item) {
                QPainterPath path = item->path();
                path.lineTo(event->scenePos());
                item->setPath(path);
            }
        }
    }
    /*else if(m_currentShape == Line) {
        if(m_currentItem != nullptr)
            delete m_currentItem;
        QLineF line(m_startPos, mouseEvent->scenePos());
        QGraphicsLineItem *item = new QGraphicsLineItem(line);
        item->setPen(QPen(QColor(Qt::red), 1));
        addItem(item);
        m_currentItem = item;
    } else if(m_currentShape != Cursor) {
        if(m_currentItem != nullptr)
            delete m_currentItem;
        QRectF rect(m_startPos, mouseEvent->scenePos());
        QGraphicsRectItem *item = new QGraphicsRectItem(rect);
        item->setPen(QPen(QColor(Qt::red), 1));
        addItem(item);
        m_currentItem = item;
    }*/
    QGraphicsScene::mouseMoveEvent(event);
}

void ImageScene::updateSceneeee()
{
    qDebug("updateScene");
//    QPen pen(m_penColor, m_penThickness);
//    m_pathItem->setPen(pen);
////    m_pathItem->setBrush(Qt::transparent);
//    QPainterPath path = m_pathItem->path();

//    int cnt = 0;
//    path.clear();
//    foreach(auto item, m_itemList) {
////        qDebug() << item->scenePos();
//        QPointF p = item->scenePos();
//        if(cnt++ == 0) {
//            path.moveTo(p.rx()+ItemWidth/2, p.ry()+ItemWidth/2);
//        } else {
//            path.lineTo(p.rx()+ItemWidth/2, p.ry()+ItemWidth/2);
//        }

//    }
//    path.closeSubpath();
//    m_pathItem->setPath(path);
}

//void ImageScene::wheelEvent(QGraphicsSceneWheelEvent *event)
//{
//    qDebug("wheelEvent");
//    int numDegrees = /*event->angleDelta().y() / */8;
//    int numSteps = numDegrees / 15; // see QWheelEvent documentation
//    _numScheduledScalings += numSteps;
//    if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
//        _numScheduledScalings = numSteps;

//    QTimeLine *anim = new QTimeLine(350, this);
//    anim->setUpdateInterval(20);

//    connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
//    connect(anim, SIGNAL (finished()), SLOT (animFinished()));
//    anim->start();
//}

//void ImageScene::scalingTime(qreal x)
//{
//    Q_UNUSED(x);
//    qreal factor = 1.0 + qreal(_numScheduledScalings) / 300.0;
////    scale(factor, factor);
//}

//void ImageScene::animFinished()
//{
//    (_numScheduledScalings > 0)?_numScheduledScalings--:_numScheduledScalings++;
//    //delete sender();     //    sender()->~QObject();
//}

//bool ImageScene::event(QEvent *event)
//{
//    if (event->type() == QEvent::Gesture)
//        return gestureEvent(static_cast<QGestureEvent*>(event));
//    return QGraphicsScene::event(event);
//}

//bool ImageScene::gestureEvent(QGestureEvent *event)
//{
//    qDebug("gestureEvent");
//    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
//        pinchTriggered(static_cast<QPinchGesture *>(pinch));
//    return true;
//}

//void ImageScene::pinchTriggered(QPinchGesture *gesture)
//{
//    qDebug("pinchTriggered");
//    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
//    if (changeFlags & QPinchGesture::RotationAngleChanged) {
//        qreal rotationDelta = gesture->rotationAngle() - gesture->lastRotationAngle();
//        _rotationAngle += rotationDelta;
//    }
//    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
//        _currentStepScaleFactor = gesture->totalScaleFactor();
//    }
//    if (gesture->state() == Qt::GestureFinished) {
//        _scaleFactor *= _currentStepScaleFactor;
//        _currentStepScaleFactor = 1;
//    }
//    update();
//}
