#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QToolBar* toolbar = addToolBar(tr("Open"));

    combo = new QComboBox;

    ListView *lv = new ListView;
    combo->setView(lv);

    combo->setEditable(true);
    combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(combo, SIGNAL(activated(int)), SLOT(openRssFeed()));
    toolbar->addWidget(combo);

    QAction *act = new QAction(tr("Open RSS Feed"), this);
    act->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    connect(act, SIGNAL(triggered()), SLOT(openRssFeed()));
    toolbar->addAction(act);

    combo->addItem("http://news.google.co.kr/news?cf=all&hl=ko&output=rss");

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::openRssFeed()
{
    manager->get(QNetworkRequest(QUrl(combo->currentText())));
}

void MainWindow::replyFinished(QNetworkReply* netReply)
{
    QString str(netReply->readAll());
    qDebug("%s", qPrintable(str));
}

void ListView::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Delete){
        event->accept();
        QModelIndexList I = selectedIndexes();
        if(I.length() > 0){
            model()->removeRow(I.at(0).row(), I.at(0).parent());
        }
    }
    else{
        QListView::keyPressEvent(event);
    }
}
