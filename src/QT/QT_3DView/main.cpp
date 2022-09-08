#include "mainwindow.h"

#include <QApplication>
#include <geometryengine.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    GeometryEngine w;
//    w.show();

    MainWindow w;
    w.show();
    return a.exec();
}
