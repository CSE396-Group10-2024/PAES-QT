/********************************************************************************
** Form generated from reading UI file 'minegame.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINEGAME_H
#define UI_MINEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_minegame
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *minegame)
    {
        if (minegame->objectName().isEmpty())
            minegame->setObjectName("minegame");
        minegame->resize(800, 600);
        centralwidget = new QWidget(minegame);
        centralwidget->setObjectName("centralwidget");
        minegame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(minegame);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        minegame->setMenuBar(menubar);
        statusbar = new QStatusBar(minegame);
        statusbar->setObjectName("statusbar");
        minegame->setStatusBar(statusbar);

        retranslateUi(minegame);

        QMetaObject::connectSlotsByName(minegame);
    } // setupUi

    void retranslateUi(QMainWindow *minegame)
    {
        minegame->setWindowTitle(QCoreApplication::translate("minegame", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class minegame: public Ui_minegame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINEGAME_H
