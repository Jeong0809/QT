#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class EditImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage *img;
    EditImage* editimage;

    void wheelEvent(QWheelEvent* event);

    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void popUpImage();

private slots:
    void ButtonClicked();
    void zoomIn();
    void on_graphicsView_customContextMenuRequested(const QPoint &pos);
    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);
};
#endif // MAINWINDOW_H
