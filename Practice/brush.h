#ifndef BRUSH_H
#define BRUSH_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsView>

class OhBrush : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawLine};
    OhBrush(QObject* parent = 0);
    void setMode(Mode mode);

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //    void keyPressEvent(QKeyEvent *event);

private:
    Mode sceneMode;
    QPointF origPoint;
    QGraphicsLineItem* itemToDraw;
    QPointF previousPoint;

    QGraphicsScene* ohBrush;


};

#endif // BRUSH_H
