#include "qteditor.h"
#include <QTextEdit>
#include <QMenuBar> //파스칼 표기법
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QStatusBar>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <QFontDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTranslator>
#include <QKeyEvent>
#include <QEvent>
#include <QCryptographicHash>
#include <QSettings>

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)   //부모클래스의 생성자를 열거형 초기화 한 것
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

#if 0
    QTextEdit* textedit = new QTextEdit(this);
    //setCentralWidget(textedit);
    mdiArea->addSubWindow(textedit);
#else

#endif

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    QMenu *fileMenu = menubar->addMenu(QObject::tr("&File"));

    QMenu *formatMenu = menubar->addMenu("&Format");

    QAction *newAct = makeAction(":/images/new.png", QObject::tr("&New"), "Ctrl+N",
                                 "make new file", this, SLOT(newFile()));
    fileMenu->addAction(newAct);

    QAction *openAct = makeAction(":/images/open.png", QObject::tr("&Open"), "Ctrl+O",
                                  "open file", this, SLOT(openFile()));
    fileMenu->addAction(openAct);

    QAction *saveAct = makeAction(":/images/save.png", QObject::tr("&Save"), "Ctrl+S",
                                  "save file", this, SLOT(saveFile()));
    fileMenu->addAction(saveAct);

    QAction *saveasAct = makeAction("", QObject::tr("&Save as"), "Ctrl+A",
                                  "save as file", this, SLOT(saveasFile()));
    fileMenu->addAction(saveasAct);

    QAction *printAct = makeAction(":/images/print.png", QObject::tr("&Print"), "Ctrl+P",
                                  "print file", this, SLOT(print()));
    fileMenu->addAction(printAct);


    QAction *quitAct = makeAction(":/images/Happy.png", QObject::tr("&Quit"), "Ctrl+Q",
                                  "quit this program", qApp, SLOT(quit()));
                                                      // QObject* recv, QString* slot
    //new QAction(QIcon("Happy.png"), "&Quit", this);
    //connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    QToolBar *fileToolBar = addToolBar(QObject::tr("&File"));
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(openAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    windowMenu = menubar->addMenu(QObject::tr("&Window"));
    windowMenu->addAction(fileToolBar->toggleViewAction());   

    QLabel *label = new QLabel("Dock Widget", this);
    QDockWidget *dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(label);
    windowMenu->addAction(dock->toggleViewAction());


    windowMenu->addSeparator();
    QAction *Cascade = makeAction("", QObject::tr("&Cascade"), "Ctrl+1", "Cascade files",
                                  mdiArea, SLOT(cascadeSubWindows()));
    windowMenu->addAction(Cascade);

    QAction *Tile = makeAction("", QObject::tr("&Tile"), "Ctrl+2", "Tile files",
                               mdiArea, SLOT(tileSubWindows()));
    windowMenu->addAction(Tile);

    QAction *Prev = makeAction("", QObject::tr("&Prev"), "Ctrl+3", "Prev files",
                               mdiArea, SLOT(activatePreviousSubWindow()));
    windowMenu->addAction(Prev);

    QAction *Next = makeAction("", QObject::tr("&Next"), "Ctrl+4", "Next files",
                               mdiArea, SLOT(activateNextSubWindow()));
    windowMenu->addAction(Next);

    QAction *Close = makeAction("", QObject::tr("&Close"), "Ctrl+5", "Close files",
                               mdiArea, SLOT(closeActiveSubWindow()));
    windowMenu->addAction(Close);

    QAction *CloseAll = makeAction("", QObject::tr("&Close All"), "Ctrl+6", "Close All files",
                               mdiArea, SLOT(closeAllSubWindows()));
    windowMenu->addAction(CloseAll);


    fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(setTextFont(QFont)));
    sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), SLOT(setTextSize(qreal)));
    addToolBarBreak();


    QToolBar *formatToolBar = addToolBar(QObject::tr("&Format"));
    formatToolBar->addSeparator();
    formatToolBar->addWidget(fontComboBox);
    formatToolBar->addWidget(sizeSpinBox);

    QStatusBar *statusbar = statusBar();
    QLabel *statusLabel = new QLabel("Qt Editor", statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started", 1500);

    QMenu *editMenu = menubar->addMenu(QObject::tr("&Edit"));
    QAction *undoact = makeAction(":/images/undo.png", tr("&Undo"), "Ctrl+U",
                                  "undo file", this, SLOT(editSlot()));
    connect(undoact, SIGNAL(triggered()), SLOT(editSlot()));
    editMenu->addAction(undoact);

    QAction *redoact = makeAction(":/images/redo.png", QObject::tr("&Redo"), "Ctrl+R",
                                  "redo file", this, SLOT(editSlot()));
    editMenu->addAction(redoact);

    QAction *copyact = makeAction(":/images/copy.png", "&Copy", "Ctrl+C",
                                  "copy file", this, SLOT(editSlot()));
    editMenu->addAction(copyact);

    QAction *cutact = makeAction(":/images/cut.png", "&Cut", "Ctrl+X",
                                  "cut file", this, SLOT(editSlot()));
    editMenu->addAction(cutact);

    QAction *pasteact = makeAction(":/images/paste.png", "&Paste", "Ctrl+P",
                                  "paste file", this, SLOT(editSlot()));
    editMenu->addAction(pasteact);
    editMenu->addSeparator();

    QAction *zoominact = makeAction(":/images/zoomin.png", "&Zoom in", "Ctrl+I",
                                  "zoom in file", this, SLOT(editSlot()));
    editMenu->addAction(zoominact);

    QAction *zoomoutact = makeAction(":/images/zoomout.png", "&Zoom out", "Ctrl+M",
                                  "zoom out file", this, SLOT(editSlot()));
    editMenu->addAction(zoomoutact);

    QMenu *alignMenu = formatMenu->addMenu("&Align");
    QAction *alignLeftArt = new QAction("&Left", this);
    QAction *alignCenterArt = new QAction("&Center", this);
    QAction *alignRightArt = new QAction("&Right", this);
    QAction *alignJustifyArt = new QAction("&Justify", this);

//    connect(alignCenterArt, SIGNAL(triggered()), textedit,
//            SLOT(setAlignment(Qt::AlignCenter)));

//    connect(alignCenterArt, SIGNAL(triggered(Qt::AlignCenter)), textedit,
//            SLOT(setAlignment(Qt::Alignment)));
//    alignMenu->addAction(alignCenterArt);

    alignMenu->addAction(alignLeftArt);
    connect(alignLeftArt, SIGNAL(triggered()), SLOT(alignText()));

    alignMenu->addAction(alignCenterArt);
    connect(alignCenterArt, SIGNAL(triggered()), SLOT(alignText()));

    alignMenu->addAction(alignRightArt);
    connect(alignRightArt, SIGNAL(triggered()), SLOT(alignText()));

    alignMenu->addAction(alignJustifyArt);
    connect(alignJustifyArt, SIGNAL(triggered()), SLOT(alignText()));


    QAction *colorMenu = makeAction("", "&Color", "",
                                  "color", this, SLOT(setColor()));
    formatMenu->addAction(colorMenu);

    QAction *fontMenu = makeAction("", "&Font", "",
                                  "font", this, SLOT(setFont()));
    formatMenu->addAction(fontMenu);

    QMenu *helpMenu = menubar->addMenu("&Help");
    QAction *About = makeAction(":/images/about.png", "&About", "", "About", this, SLOT(about()));
    QAction *AboutQT = new QAction("&About Qt", this);

    helpMenu->addAction(About);
    helpMenu->addAction(AboutQT);
    connect(AboutQT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    newFile();

    readSettings();
}

void QtEditor::writeSettings()
{
    QSettings settings("QtEditor.ini", QSettings::IniFormat);
    settings.beginGroup("QtEditor");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("fullScreen", isFullScreen());
    settings.endGroup();
}

void QtEditor::readSettings()
{
    QSettings settings("QtEditor.ini", QSettings::IniFormat);
    settings.beginGroup("QtEditor");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());

    if(settings.value("fullScreen").toBool())
        setWindowState(windowState()^Qt::WindowFullScreen);
    settings.endGroup();
}

void QtEditor::closeEvent(QCloseEvent* event)
{
    writeSettings();
    event->accept();
}

void QtEditor::setFontWidget()
{
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = textedit->currentFont();
    fontComboBox->setCurrentFont(font);
    sizeSpinBox->setValue(font.pointSizeF());
}

void QtEditor::selectWindow()
{
    QTextEdit *textedit = (QTextEdit*)windowHash[(QAction*)sender()];
    if(textedit)
        textedit->setFocus();
}

void QtEditor::print()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);

    if(printDialog.exec() == QDialog::Accepted){
        QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->print(&printer);
    }
}

void QtEditor::setFont()
{
    bool ok;
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = QFontDialog::getFont(&ok, textedit->currentFont(), this);
    if(ok)
        textedit->setCurrentFont(font);
}

void QtEditor::setColor()
{
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor(textedit->textColor(), this);
    if(color.isValid())
        textedit->setTextColor(color);
}

void QtEditor::about(){
    QMessageBox::question(this, "QMessageBox", "Question Message",
                          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
}

void QtEditor::setTextSize(qreal size){
    //QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QMdiSubWindow *subwindow = mdiArea->currentSubWindow();
    QTextEdit *textedit = dynamic_cast<QTextEdit*>(subwindow->widget());
    QFont font = textedit->currentFont();
    font.setPointSizeF(size);
    textedit->setCurrentFont(font);
}

void QtEditor::setTextFont(QFont font){
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->setCurrentFont(font);
}

void QtEditor::alignText(){
    QAction *action = qobject_cast<QAction*>(sender());
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());

    if(action->text() == "&Center")
        textedit->setAlignment(Qt::AlignCenter);
    else if(action->text() == "&Left")
        textedit->setAlignment(Qt::AlignLeft);
    else if(action->text() == "&Right")
        textedit->setAlignment(Qt::AlignRight);
    else if(action->text() == "&Justify")
        textedit->setAlignment(Qt::AlignJustify);
}

void QtEditor::editSlot(){
    QAction *action = qobject_cast<QAction*>(sender());
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());

    if(subWindow != nullptr){
        if(action->text() == "&Undo")
            textedit->undo();

        else if(action->text() == "&Redo")
            textedit->redo();

        else if(action->text() == "&Copy")
            textedit->copy();

        else if(action->text() == "&Cut")
            textedit->cut();

        else if(action->text() == "&Paste")
            textedit->paste();

        else if(action->text() == "&Zoom in")
            textedit->zoomIn();

        else if(action->text() == "&Zoom out")
            textedit->zoomOut();
    }
}

QAction *QtEditor::makeAction(QString icon, QString name, QString shortCut,
                              QString toolTip, QObject *recv, const char* slot)
{
    QAction *act = new QAction(name, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered()), recv, slot);
    return act;
}

void QtEditor::saveasFile()
{
    qDebug("save File");
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save as", ".",
                                                    "Text File (*.txt *.html *.c *.cpp *.h)");


    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QFileInfo fileInfo(filename);

    if(fileInfo.isWritable()){
        QByteArray msg = textedit->toHtml().toUtf8();
        file->write(msg);
        textedit->setWindowTitle(filename);
        QAction *action = windowHash.key(textedit);     // windowHash[키]
        action->setText(filename);
    }
    else{
        QMessageBox::warning(this, "Error", "Can't Save this file",
                             QMessageBox::Ok);
    }

    file->close();
    delete file;
    //qDebug()<<filename;
}

void QtEditor::saveFile()
{
    qDebug("save File");
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QString filename = textedit->windowTitle();
    if(!filename.length()){
        filename = QFileDialog::getSaveFileName(this, "Select a file to save", ".",
                                                "Text File (*.txt *.html *.c *.cpp *.h)");

    }

    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QFileInfo fileInfo(filename);

    if(fileInfo.isWritable()){
        QByteArray msg = textedit->toHtml().toUtf8();
        file->write(msg);
        textedit->setWindowTitle(filename);
        QAction *action = windowHash.key(textedit);     // windowHash[키]
        action->setText(filename);
    }
    else{
        QMessageBox::warning(this, "Error", "Can't Save this file",
                             QMessageBox::Ok);
    }

    file->close();
    delete file;
    //qDebug()<<filename;
}

void QtEditor::openFile()
{
    qDebug("open file");
    QString filename = QFileDialog::getOpenFileName(this, "Select file to open", ".",
                                                    "Text File (*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
    QFileInfo fileInfo(filename);

    if(fileInfo.isReadable()){
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QByteArray msg = file.readAll();
        file.close();

        newFile();
        QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->setWindowTitle(filename);

        QAction *action = windowHash.key(textedit);     // windowHash[키]
        action->setText(filename);

        if(fileInfo.suffix() == "htm" || fileInfo.suffix() == "html")
            textedit->setHtml(msg);
        else
            textedit->setPlainText(msg);
        //mdiArea->addSubWindow(textedit);
        textedit->show();
    }

    else{
        QMessageBox::warning(this, "Error", "Can't Read this file",
                             QMessageBox::Ok);
    }
}

void QtEditor::newFile()
{   
    qDebug("Make New File");
    QAction* windowAct = new QAction("New File", this);
    windowMenu->addAction(windowAct);
    QTextEdit *textedit = new QTextEdit;

    connect(textedit, SIGNAL(destroyed(QObject*)), windowAct, SLOT(deleteLater()));
//    connect(textedit, SIGNAL(destroyed(QObject*)), this, SLOT(closeWindow()));
    connect(textedit, SIGNAL(cursorPositionChanged()), SLOT(setFontWidget()));
    mdiArea->addSubWindow(textedit);

    windowHash[windowAct] = textedit;
    connect(windowAct, SIGNAL(triggered()), SLOT(selectWindow()));
    connect(textedit, SIGNAL(destroyed(QObject*)), windowAct, SLOT(deleteLater()));


    textedit->installEventFilter(this);
    textedit->show();

}

bool QtEditor::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        qDebug("Key press %d", keyEvent->key());
        return false;
    }
    else{
        return QObject::eventFilter(obj, event);
    }
}


QtEditor::~QtEditor()
{
}

