#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <GL/glu.h>

class Widget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void drawPyramid();

    GLfloat xAngle, yAngle, zAngle;
    GLfloat left, right, bottom, top, bNear, bFar;
    GLfloat fov;
    int bProjection;
    int bObject;
    GLsizei lastWidth, lastHeight;

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

protected:
    void keyPressEvent(QKeyEvent* event);
};
#endif // WIDGET_H
