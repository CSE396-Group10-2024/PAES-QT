/********************************************************************************
** Form generated from reading UI file 'simongamescene.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMONGAMESCENE_H
#define UI_SIMONGAMESCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simongamescene
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *simongamescene)
    {
        if (simongamescene->objectName().isEmpty())
            simongamescene->setObjectName("simongamescene");
        simongamescene->resize(800, 600);
        centralwidget = new QWidget(simongamescene);
        centralwidget->setObjectName("centralwidget");
        simongamescene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(simongamescene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        simongamescene->setMenuBar(menubar);
        statusbar = new QStatusBar(simongamescene);
        statusbar->setObjectName("statusbar");
        simongamescene->setStatusBar(statusbar);

        retranslateUi(simongamescene);

        QMetaObject::connectSlotsByName(simongamescene);
    } // setupUi

    void retranslateUi(QMainWindow *simongamescene)
    {
        simongamescene->setWindowTitle(QCoreApplication::translate("simongamescene", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simongamescene: public Ui_simongamescene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMONGAMESCENE_H
