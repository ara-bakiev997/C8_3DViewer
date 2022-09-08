#include "widget.h"

#include <QApplication>

/*

  Справка(буэ, знаю) по кодам, с которыми
    может завершиться программа:

    -230 : не скомпилировался вершинный шейдер
    -229 : не скомпилировался пиксельный шейдер
    -228 : шейдеры не слинковались

 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
