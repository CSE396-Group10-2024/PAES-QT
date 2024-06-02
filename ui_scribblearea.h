/********************************************************************************
** Form generated from reading UI file 'scribblearea.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIBBLEAREA_H
#define UI_SCRIBBLEAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScribbleArea
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScribbleArea)
    {
        if (ScribbleArea->objectName().isEmpty())
            ScribbleArea->setObjectName("ScribbleArea");
        ScribbleArea->resize(800, 600);
        centralwidget = new QWidget(ScribbleArea);
        centralwidget->setObjectName("centralwidget");
        ScribbleArea->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ScribbleArea);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        ScribbleArea->setMenuBar(menubar);
        statusbar = new QStatusBar(ScribbleArea);
        statusbar->setObjectName("statusbar");
        ScribbleArea->setStatusBar(statusbar);

        retranslateUi(ScribbleArea);

        QMetaObject::connectSlotsByName(ScribbleArea);
    } // setupUi

    void retranslateUi(QMainWindow *ScribbleArea)
    {
        ScribbleArea->setWindowTitle(QCoreApplication::translate("ScribbleArea", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScribbleArea: public Ui_ScribbleArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIBBLEAREA_H
