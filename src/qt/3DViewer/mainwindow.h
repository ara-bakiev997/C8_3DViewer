#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>

#include <QOpenGLWidget>

#include <QMessageBox>
//_________GIF
#include <Qlabel>
#include <QPixmap>
#include <QScreen>
#include <vector>
#include <cstdint>
#include <QTimer>
#include <QSettings>
#include <QTextEdit>
#include <math.h>
#include "QtGifImage-master/src/gifimage/qgifimage.h"
#include <QPainter>
#include <QImage>
//__________________

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>


#include <QtWidgets/QWidget>
#include <QtOpenGL>

#include <QFileDialog>















extern "C" {
#include "../../parser.h"
}


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //___ GIF
    QVector<QImage> mas_image;

private slots:

    void on_openTestFile_clicked();

    void on_openLamp_clicked();

    void on_parse_clicked();

    void on_openFile_clicked();

    void on_Pthoto_clicked();

    //_______GIF
    void create_screen();

    void on_stop_and_save_GIF_clicked();

    void save_gif();

private:
    Ui::MainWindow *ui;

    //_____GIF
    QTimer *timer;
    QTimer *timer_for_gif;
    QThread* somethread;
    double time = 0;
    int xyz = 1;
    int flag_record = 0;
};
#endif // MAINWINDOW_H
