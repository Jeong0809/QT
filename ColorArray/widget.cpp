#include "widget.h"
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    xAngle = 120, yAngle = 30, zAngle = 75;
    setWindowTitle("OpenGL ColorArray");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Widget::resizeGL(int w, int h)
{
   glViewport(0, 0, (GLint)w, (GLint)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL()
{
    static GLfloat vertcolor[] = {
        1, 1, 1, 0, 0, -0.8,
        0, 0, 1, 0.5, 0.5, 0,
        1, 0, 0, -0.5, 0.5, 0,
        1, 1, 0, -0.5, -0.5, 0,
        0, 1, 0, 0.5, -0.5, 0,
    };

    static GLfloat color[] = {
        1.0, 1.0, 1.0,
        0.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
    };

    static GLubyte index[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(1, 1, 1);
    glRectf(-0.5, 0.5, 0.5, -0.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*6, &vertcolor[3]);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(GLfloat)*6, vertcolor);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, index);

    glPopMatrix();
    glFlush();

}































