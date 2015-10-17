#include "mainwindow.h"
#include "servicemgr.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ServiceMgr s;
    s.init();

    MainWindow w;
    w.show();

    int result = a.exec();
    s.shutdown();
    return result;
}
