#include "brush.h"
#include "widget.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QGraphicsScene>



class Widget;

OhBrush::OhBrush(QObject* parent) : QGraphicsScene(parent)
{
}

void OhBrush::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "Hi";
    origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);


//    ohBrush->addEllipse(event->pos().x() - 5,
//                        event->pos().y() - 5,
//                        10,
//                        10,
//                        QPen(Qt::NoPen),
//                        QBrush(Qt::red));
//    previousPoint = event->pos();

}


void OhBrush::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    qDebug() << "Hi2222222222";
    itemToDraw = new QGraphicsLineItem;
    itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
    itemToDraw->setPos(origPoint);
    //        }
    itemToDraw->setLine(0, 0,
                        event->scenePos().x() - origPoint.x(),
                        event->scenePos().y() - origPoint.y());
    //    }
    //    else
    QGraphicsScene::mouseMoveEvent(event);
//    this->sendEvent( event);
}

void OhBrush::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "Hi3333";
    itemToDraw = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

