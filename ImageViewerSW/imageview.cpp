#include <QMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QTimeLine>
#include <QPinchGesture>
#include <QGraphicsItem>

#include "imageview.h"

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
{
    graphicsScene = new QGraphicsScene(this);
    setScene(graphicsScene);

    _pan = false;
    _currentStepScaleFactor = 1;

    resetTransform();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void ImageView::ReceiveInfo(const QColor& paintColor, int value)
{
    m_penColor = paintColor;
    m_penThickness = value;
    qDebug() << "ImageView : " << m_penColor;
    qDebug() << "ImageView : " << m_penThickness;
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    qDebug("mousePressEvent");

    if (event->button() == Qt::LeftButton) {
        startPos = mapToScene(event->pos());
        graphicsScene->addRect(startPos.x(), startPos.y(),
                               50, 50,
                               QPen(Qt::NoPen),
                               QBrush(m_penColor));
        setCursor(Qt::ClosedHandCursor);
        _pan = true;
        event->accept();
        return;
    }
    event->ignore();
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug("mouseReleaseEvent");

    if(_pan){
        setCursor(Qt::ArrowCursor);
        event->accept();
    }
    _pan = false;
    event->ignore();
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug("mouseMoveEvent");

    this->setDragMode(QGraphicsView::NoDrag);
    QPointF newPos = mapToScene(event->pos());

    if(_pan){
        qDebug() << "Mouse pressed in view at position (Scene Coord) : " << newPos;
        graphicsScene->addLine(startPos.x(), startPos.y(),
                               newPos.x(), newPos.y(),
                               QPen(m_penColor, m_penThickness, Qt::SolidLine, Qt::RoundCap));
        event->accept();
    }

    event->ignore();
    startPos = newPos;
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    qDebug("wheelEvent");
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15; // see QWheelEvent documentation
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
        _numScheduledScalings = numSteps;

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
    connect(anim, SIGNAL (finished()), SLOT (animFinished()));
    anim->start();
}

void ImageView::scalingTime(qreal x)
{
    Q_UNUSED(x);
    qreal factor = 1.0 + qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);
}

void ImageView::animFinished()
{
    (_numScheduledScalings > 0)?_numScheduledScalings--:_numScheduledScalings++;
    //delete sender();     //    sender()->~QObject();
}

bool ImageView::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QGraphicsView::event(event);
}

bool ImageView::gestureEvent(QGestureEvent *event)
{
    qDebug("gestureEvent");
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    return true;
}

void ImageView::pinchTriggered(QPinchGesture *gesture)
{
    qDebug("pinchTriggered");
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if (changeFlags & QPinchGesture::RotationAngleChanged) {
        qreal rotationDelta = gesture->rotationAngle() - gesture->lastRotationAngle();
        _rotationAngle += rotationDelta;
    }
    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        _currentStepScaleFactor = gesture->totalScaleFactor();
    }
    if (gesture->state() == Qt::GestureFinished) {
        _scaleFactor *= _currentStepScaleFactor;
        _currentStepScaleFactor = 1;
    }
    update();
}
