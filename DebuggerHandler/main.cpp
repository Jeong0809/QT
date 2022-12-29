#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>

void myDebugMsg(QtMsgType type, const QMessageLogContext &context,
                const QString &msg)
{
    switch(type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug : %s\n", qPrintable(msg));
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning : %s\n", qPrintable(msg));
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal : %s\n", qPrintable(msg));
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myDebugMsg);
    QCoreApplication a(argc, argv);
    qDebug();
    return a.exec();
}













