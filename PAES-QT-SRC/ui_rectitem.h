/********************************************************************************
** Form generated from reading UI file 'rectitem.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTITEM_H
#define UI_RECTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rectitem
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *rectitem)
    {
        if (rectitem->objectName().isEmpty())
            rectitem->setObjectName("rectitem");
        rectitem->resize(800, 600);
        centralwidget = new QWidget(rectitem);
        centralwidget->setObjectName("centralwidget");
        rectitem->setCentralWidget(centralwidget);
        menubar = new QMenuBar(rectitem);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        rectitem->setMenuBar(menubar);
        statusbar = new QStatusBar(rectitem);
        statusbar->setObjectName("statusbar");
        rectitem->setStatusBar(statusbar);

        retranslateUi(rectitem);

        QMetaObject::connectSlotsByName(rectitem);
    } // setupUi

    void retranslateUi(QMainWindow *rectitem)
    {
        rectitem->setWindowTitle(QCoreApplication::translate("rectitem", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rectitem: public Ui_rectitem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTITEM_H
