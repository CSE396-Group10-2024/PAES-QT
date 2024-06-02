/********************************************************************************
** Form generated from reading UI file 'bejewgame.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEJEWGAME_H
#define UI_BEJEWGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bejewgame
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *bejewgame)
    {
        if (bejewgame->objectName().isEmpty())
            bejewgame->setObjectName("bejewgame");
        bejewgame->resize(800, 600);
        centralwidget = new QWidget(bejewgame);
        centralwidget->setObjectName("centralwidget");
        bejewgame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(bejewgame);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        bejewgame->setMenuBar(menubar);
        statusbar = new QStatusBar(bejewgame);
        statusbar->setObjectName("statusbar");
        bejewgame->setStatusBar(statusbar);

        retranslateUi(bejewgame);

        QMetaObject::connectSlotsByName(bejewgame);
    } // setupUi

    void retranslateUi(QMainWindow *bejewgame)
    {
        bejewgame->setWindowTitle(QCoreApplication::translate("bejewgame", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bejewgame: public Ui_bejewgame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEJEWGAME_H
