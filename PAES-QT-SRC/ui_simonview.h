/********************************************************************************
** Form generated from reading UI file 'simonview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMONVIEW_H
#define UI_SIMONVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simonview
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *simonview)
    {
        if (simonview->objectName().isEmpty())
            simonview->setObjectName("simonview");
        simonview->resize(800, 600);
        centralwidget = new QWidget(simonview);
        centralwidget->setObjectName("centralwidget");
        simonview->setCentralWidget(centralwidget);
        menubar = new QMenuBar(simonview);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        simonview->setMenuBar(menubar);
        statusbar = new QStatusBar(simonview);
        statusbar->setObjectName("statusbar");
        simonview->setStatusBar(statusbar);

        retranslateUi(simonview);

        QMetaObject::connectSlotsByName(simonview);
    } // setupUi

    void retranslateUi(QMainWindow *simonview)
    {
        simonview->setWindowTitle(QCoreApplication::translate("simonview", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simonview: public Ui_simonview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMONVIEW_H
