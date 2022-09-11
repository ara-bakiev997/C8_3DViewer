#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_openTestFile_clicked() {
     ui->label->setText("/Users/violator/C8_3DViewer_v1.0-1/src/objFiles/cube.obj");
}


void MainWindow::on_openLamp_clicked(){
    ui->label->setText("/Users/violator/C8_3DViewer_v1.0-1/src/objFiles/lamp.obj");
}


void MainWindow::on_parse_clicked() {
    QString fileName = ui->label->text();
    QByteArray ba = fileName.toLocal8Bit();
    char *str = ba.data();
    int error = 0;
    error = parser(str, &ui->widget->vertex, &ui->widget->facet);

    if(!error) {
        std::cout << error << std::endl;
        std::cout << str << std::endl;

        ui->widget->scale = ui->scale->text().toFloat();
    } else if (error == 1) {
        ui->label->setText("ERROR: File not found");
    }


//    for (unsigned int a = 1; a < vertex.count; a++) {
//        std::cout << vertex.arg_v[a] << "\t";
//        if (a % 3 == 0) {
//           std::cout << std::endl;
//        }
//    }

//    std::cout << std::endl;

//    for (unsigned int a = 1; a < facet.count; a++) {
//        std::cout << facet.arg_f[a] << "\t";
//        if (a % 6 == 0) {
//           std::cout << std::endl;
//        }
//    }

//    for (int a = 0; a < facet.matrix.rows; a++) {
//            for (int b = 0; b <facet.matrix.columns; b++) {
//                std::cout << facets.matrix.matrix[a][b] << "\t";
//            }
//            std::cout << std::endl;
//        }
}


void MainWindow::on_openFile_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::homePath(), tr( " (*.obj)"));
    ui->label->setText(fileName);
}


void MainWindow::on_Pthoto_clicked()
{
//    img.save(QFileDialog::getSaveFileName(0,tr("Save image"),QDir::currentPath(),"*.ico *.png *.jpg"));

//    QString type = "";
//      QMessageBox::StandardButton reply;
//      reply =
//          QMessageBox::question(this, "Whot do you want?", "No - JPG, Yes - BMP",
//                                QMessageBox::Yes | QMessageBox::No);
//      if (reply == QMessageBox::Yes) {
//        type = "bmp (*.bmp)";
//      } else if (reply == QMessageBox::No) {
//        type = "jpg (*.jpg)";
//      }
      QFileDialog file_dialog_photo(this);
      QString f_name_photo =
          file_dialog_photo.getSaveFileName(0,tr("Save image"),QDir::currentPath(),"*.ico *.png *.jpg");
      QFile file(f_name_photo);
      file.open(QIODevice::WriteOnly);
      QRect rect(0, 0, ui->widget->width(), ui->widget->height());
      QPixmap pixmap = ui->widget->grab(rect);
      pixmap.copy(rect);
      pixmap.toImage().save(&file, "jpg");
      QString q_command_line = "open " + f_name_photo;
      QByteArray temp = q_command_line.toLocal8Bit();
      char *command_line = temp.data();
      system(command_line);


//    QString type = "";
//      QMessageBox::StandardButton reply;
//      reply =
//          QMessageBox::question(this, "Whot do you want?", "No - JPG, Yes - BMP",
//                                QMessageBox::Yes | QMessageBox::No);
//      if (reply == QMessageBox::Yes) {
//        type = "bmp (*.bmp)";
//      } else if (reply == QMessageBox::No) {
//        type = "jpg (*.jpg)";
//      }
//      QFileDialog file_dialog_photo(this);
//      QString f_name_photo =
//          file_dialog_photo.getSaveFileName(this, tr("Save a gif"), "", type);
//      QFile file(f_name_photo);
//      file.open(QIODevice::WriteOnly);
//      QRect rect(0, 0, ui->widget->width(), ui->widget->height());
//      QPixmap pixmap = ui->widget->grab(rect);
//      pixmap.copy(rect);
//      pixmap.toImage().save(&file, "jpg");
//      QString q_command_line = "open " + f_name_photo;
//      QByteArray temp = q_command_line.toLocal8Bit();
//      char *command_line = temp.data();
//      system(command_line);
}

