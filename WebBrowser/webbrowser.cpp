#include "webbrowser.h"
#include <QUrl>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QLineEdit>
#include <QWebEngineHistory>
#include <QApplication>
#include <QStatusBar>

webbrowser::webbrowser(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);
    webEngineView = new QWebEngineView(this);
    webEngineView->setUrl(QUrl("https://www.naver.com/"));
    lineEditURL = new QLineEdit(this);
    connect(lineEditURL, SIGNAL(returnPressed()), SLOT(goSlot()));

    QAction* actionOpen = new QAction("Open", this);
    connect(actionOpen, SIGNAL(triggered()), SLOT(goSlot()));
    QAction* actionQuit = new QAction("Quit", this);
    connect(actionQuit, SIGNAL(triggered()), SLOT(goSlot()));

    QAction* actionGo = new QAction("Go", this);
    connect(actionGo, SIGNAL(triggered()), SLOT(goSlot()));

    QAction* actionBackward = new QAction("Back", this);
    connect(actionBackward, SIGNAL(triggered()), SLOT(goBackwardSlot()));

    QAction* actionForward = new QAction("Forward", this);
    connect(actionForward, SIGNAL(triggered()), SLOT(goForwardSlot()));

    QAction* actionHome = new QAction("Home", this);
    connect(actionHome, SIGNAL(triggered()), SLOT(goHomeSlot()));

    QAction* actionReload = new QAction("Reload", this);
    connect(actionReload, SIGNAL(triggered()), webEngineView, SLOT(reload()));
    QAction* actionStop = new QAction("Stop", this);
    connect(actionStop, SIGNAL(triggered()), webEngineView, SLOT(stop()));
    QAction* actionAbout = new QAction("About", this);
    connect(actionAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    QMenuBar* menubar = menuBar();

    QMenu* menufile = new QMenu("&File", menubar);
    menufile->addAction(actionOpen);
    menufile->addSeparator();
    menufile->addAction(actionQuit);
    menubar->addMenu(menufile);

    QMenu* menuView = new QMenu("&View", menubar);
    menuView->addAction(actionGo);
    menuView->addAction(actionBackward);
    menuView->addAction(actionForward);
    menuView->addAction(actionStop);
    menuView->addAction(actionReload);
    menuView->addSeparator();
    menuView->addAction(actionHome);
    menubar->addMenu(menuView);

    QMenu* menuHelp = new QMenu("&Help", menubar);
    menuHelp->addAction(actionAbout);
    menubar->addMenu(menuHelp);

    QToolBar* toolBarNavigation = new QToolBar("Navigation", this);
    toolBarNavigation->addAction(actionBackward);
    toolBarNavigation->addAction(actionForward);
    toolBarNavigation->addSeparator();
    toolBarNavigation->addAction(actionReload);
    toolBarNavigation->addAction(actionStop);
    toolBarNavigation->addSeparator();
    toolBarNavigation->addWidget(lineEditURL);
    addToolBar(Qt::TopToolBarArea, toolBarNavigation);

    QStatusBar* statusbar = statusBar();

    setCentralWidget(webEngineView);
}

webbrowser::~webbrowser()
{
}

void webbrowser::goSlot()
{
    QUrl url(lineEditURL->text());
    webEngineView->load(url);
}

void webbrowser::goBackwardSlot()
{
    QWebEngineHistory* history = webEngineView->history();
    if(history->canGoBack()) history->back();
}

void webbrowser::goForwardSlot()
{
    QWebEngineHistory* history = webEngineView->history();
    if(history->canGoForward()) history->forward();
}

void webbrowser::goHomeSlot()
{
    QUrl url(lineEditURL->text());
    webEngineView->load(url);
}










