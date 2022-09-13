#include "mainwindow.h"

#include <QApplication>




int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    setlocale( LC_ALL, "C" );

//    glutInit(&argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
