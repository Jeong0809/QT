#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>

class Widget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    bool alias;
    bool hint;
//    GLfloat alpha;
//    GLenum src;
//    GLenum dest;

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

protected:
    void keyPressEvent(QKeyEvent* event);

};
#endif // WIDGET_H
