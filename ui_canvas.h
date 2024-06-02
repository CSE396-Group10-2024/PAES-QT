/********************************************************************************
** Form generated from reading UI file 'canvas.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANVAS_H
#define UI_CANVAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Canvas
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Canvas)
    {
        if (Canvas->objectName().isEmpty())
            Canvas->setObjectName("Canvas");
        Canvas->resize(800, 600);
        centralwidget = new QWidget(Canvas);
        centralwidget->setObjectName("centralwidget");
        Canvas->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Canvas);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        Canvas->setMenuBar(menubar);
        statusbar = new QStatusBar(Canvas);
        statusbar->setObjectName("statusbar");
        Canvas->setStatusBar(statusbar);

        retranslateUi(Canvas);

        QMetaObject::connectSlotsByName(Canvas);
    } // setupUi

    void retranslateUi(QMainWindow *Canvas)
    {
        Canvas->setWindowTitle(QCoreApplication::translate("Canvas", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Canvas: public Ui_Canvas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVAS_H
