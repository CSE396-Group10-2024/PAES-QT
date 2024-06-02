/********************************************************************************
** Form generated from reading UI file 'simongame.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMONGAME_H
#define UI_SIMONGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simongame
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *simongame)
    {
        if (simongame->objectName().isEmpty())
            simongame->setObjectName("simongame");
        simongame->resize(800, 600);
        centralwidget = new QWidget(simongame);
        centralwidget->setObjectName("centralwidget");
        simongame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(simongame);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        simongame->setMenuBar(menubar);
        statusbar = new QStatusBar(simongame);
        statusbar->setObjectName("statusbar");
        simongame->setStatusBar(statusbar);

        retranslateUi(simongame);

        QMetaObject::connectSlotsByName(simongame);
    } // setupUi

    void retranslateUi(QMainWindow *simongame)
    {
        simongame->setWindowTitle(QCoreApplication::translate("simongame", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simongame: public Ui_simongame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMONGAME_H
