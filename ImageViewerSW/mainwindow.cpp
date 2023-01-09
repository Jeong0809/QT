#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagealbum.h"

#include <QFileDialog>
#include <QColorSpace>
#include <QMessageBox>
#include <QImageReader>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_memoAlbum = new ImageAlbum(this);

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(m_memoAlbum);
    ui->mdiArea->setActiveSubWindow(cw);
    m_memoAlbum->showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}


