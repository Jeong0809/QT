#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QMainWindow>
#include <QWebEngineView>

class QLineEdit;

class webbrowser : public QMainWindow
{
    Q_OBJECT

public:
    webbrowser(QWidget *parent = nullptr);
    ~webbrowser();

private:
    QLineEdit* lineEditURL;
    QWebEngineView* webEngineView;

public slots:
    void goSlot();
    void goBackwardSlot();
    void goForwardSlot();
    void goHomeSlot();
};
#endif // WEBBROWSER_H
