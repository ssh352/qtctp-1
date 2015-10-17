#include "ui/mainwindow.h"
#include "servicemgr.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ServiceMgr s;
    s.init();

    MainWindow w;
    w.init();
    w.show();

    int result = a.exec();

    w.shutdown();
    s.shutdown();

    return result;
}
