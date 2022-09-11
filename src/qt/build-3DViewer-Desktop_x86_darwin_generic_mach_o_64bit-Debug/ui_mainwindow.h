/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *openFile;
    QLabel *label;
    GLWidget *widget;
    QPushButton *openLamp;
    QLineEdit *scale;
    QPushButton *quit;
    QPushButton *parse;
    QPushButton *openTestFile;
    QPushButton *Pthoto;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1139, 907);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openFile = new QPushButton(centralwidget);
        openFile->setObjectName(QString::fromUtf8("openFile"));
        openFile->setGeometry(QRect(10, 250, 100, 32));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 400, 60));
        label->setStyleSheet(QString::fromUtf8("color: blue;\n"
"background-color: white;\n"
"\n"
"border-style: double;\n"
"border-width: 5px;\n"
"border-color: gray;"));
        widget = new GLWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(150, 80, 981, 761));
        widget->setStyleSheet(QString::fromUtf8("border-style: double;\n"
"border-width: 5px;\n"
"border-color: gray;"));
        openLamp = new QPushButton(centralwidget);
        openLamp->setObjectName(QString::fromUtf8("openLamp"));
        openLamp->setGeometry(QRect(10, 140, 100, 32));
        scale = new QLineEdit(centralwidget);
        scale->setObjectName(QString::fromUtf8("scale"));
        scale->setGeometry(QRect(420, 0, 113, 21));
        quit = new QPushButton(centralwidget);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setGeometry(QRect(10, 400, 100, 32));
        parse = new QPushButton(centralwidget);
        parse->setObjectName(QString::fromUtf8("parse"));
        parse->setGeometry(QRect(10, 360, 100, 32));
        openTestFile = new QPushButton(centralwidget);
        openTestFile->setObjectName(QString::fromUtf8("openTestFile"));
        openTestFile->setGeometry(QRect(10, 100, 100, 32));
        Pthoto = new QPushButton(centralwidget);
        Pthoto->setObjectName(QString::fromUtf8("Pthoto"));
        Pthoto->setGeometry(QRect(10, 460, 100, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1139, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(quit, &QPushButton::released, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "3DViewer", nullptr));
        openFile->setText(QCoreApplication::translate("MainWindow", "open file", nullptr));
        label->setText(QString());
        openLamp->setText(QCoreApplication::translate("MainWindow", "open lamp", nullptr));
        scale->setText(QCoreApplication::translate("MainWindow", "0.01", nullptr));
        quit->setText(QCoreApplication::translate("MainWindow", "quit", nullptr));
        parse->setText(QCoreApplication::translate("MainWindow", "parse", nullptr));
        openTestFile->setText(QCoreApplication::translate("MainWindow", "open test cube", nullptr));
        Pthoto->setText(QCoreApplication::translate("MainWindow", "Pthoto", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
