#ifndef QTEDITOR_H
#define QTEDITOR_H
#include <QMainWindow>
#include <QTextEdit>
#include <QFontComboBox>
#include <QDoubleSpinBox>

class QLabel;
class QMdiArea;

class QAction;
class QtEditor : public QMainWindow
{
    Q_OBJECT

private:
    QAction *makeAction(QString icon, QString name, QString shortCut,
                        QString toolTip, QObject *recv, const char* slot);    
    QTextEdit* textedit;
    QLabel* statusLabel;
    QMdiArea* mdiArea;
    QFontComboBox *fontComboBox;
    QDoubleSpinBox *sizeSpinBox;
    QHash<QAction*, QWidget*> windowHash;
    QMenu *windowMenu;

    void writeSettings();
    void readSettings();
    void closeEvent(QCloseEvent* event);

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    //우리가 만든 함수 슬롯은 connect 내에서 3번째 인자가 this이다.
    //그리고 4번째 인자를 보고 3번째 인자를 결정하면 된다.
    //connect(AboutQT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));에서 aboutQt() 슬롯은 qApp안에 있는 함수이므로
    //3번째 인자가 qApp이다.
    void newFile();
    void editSlot();
    void setTextFont(QFont font);
    void setTextSize(qreal size);
    void openFile();
    void saveFile();
    void saveasFile();
    void alignText();
    void about();
    void setColor();
    void setFont();
    void print();
    void selectWindow();
    void setFontWidget();

};
#endif // QTEDITOR_H
