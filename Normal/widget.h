#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <GL/glut.h>

class Widget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    GLboolean xAngle, yAngle, zAngle;
    GLboolean bNormal;

    void getNormal(GLfloat a[3], GLfloat b[3], GLfloat c[3],
                    GLfloat normal[3]);

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

protected:
    void keyPressEvent(QKeyEvent* event);


};
#endif // WIDGET_H
