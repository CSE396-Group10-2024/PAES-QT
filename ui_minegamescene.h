/********************************************************************************
** Form generated from reading UI file 'minegamescene.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINEGAMESCENE_H
#define UI_MINEGAMESCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_minegamescene
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *minegamescene)
    {
        if (minegamescene->objectName().isEmpty())
            minegamescene->setObjectName("minegamescene");
        minegamescene->resize(800, 600);
        centralwidget = new QWidget(minegamescene);
        centralwidget->setObjectName("centralwidget");
        minegamescene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(minegamescene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        minegamescene->setMenuBar(menubar);
        statusbar = new QStatusBar(minegamescene);
        statusbar->setObjectName("statusbar");
        minegamescene->setStatusBar(statusbar);

        retranslateUi(minegamescene);

        QMetaObject::connectSlotsByName(minegamescene);
    } // setupUi

    void retranslateUi(QMainWindow *minegamescene)
    {
        minegamescene->setWindowTitle(QCoreApplication::translate("minegamescene", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class minegamescene: public Ui_minegamescene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINEGAMESCENE_H
