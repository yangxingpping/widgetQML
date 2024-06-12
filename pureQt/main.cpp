#include "mainwindow.h"
#include "ZRectangle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    auto typeidx = qmlRegisterType<ZRectangle>("pureQt", 1, 0, "ZRectangle");
    w.setWindowFlags(w.windowFlags() | Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
