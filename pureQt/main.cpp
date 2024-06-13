#include "mainwindow.h"
#include "ZRectangle.h"
#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQmlApplicationEngine en(&a);
    //en.loadFromModule("pureQt", "ZRectangle");
    MainWindow w(&en);
    w.setWindowFlags(w.windowFlags() | Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
