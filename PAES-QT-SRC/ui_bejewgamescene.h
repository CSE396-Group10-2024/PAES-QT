/********************************************************************************
** Form generated from reading UI file 'bejewgamescene.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEJEWGAMESCENE_H
#define UI_BEJEWGAMESCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bejewgamescene
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *bejewgamescene)
    {
        if (bejewgamescene->objectName().isEmpty())
            bejewgamescene->setObjectName("bejewgamescene");
        bejewgamescene->resize(800, 600);
        centralwidget = new QWidget(bejewgamescene);
        centralwidget->setObjectName("centralwidget");
        bejewgamescene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(bejewgamescene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        bejewgamescene->setMenuBar(menubar);
        statusbar = new QStatusBar(bejewgamescene);
        statusbar->setObjectName("statusbar");
        bejewgamescene->setStatusBar(statusbar);

        retranslateUi(bejewgamescene);

        QMetaObject::connectSlotsByName(bejewgamescene);
    } // setupUi

    void retranslateUi(QMainWindow *bejewgamescene)
    {
        bejewgamescene->setWindowTitle(QCoreApplication::translate("bejewgamescene", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bejewgamescene: public Ui_bejewgamescene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEJEWGAMESCENE_H
