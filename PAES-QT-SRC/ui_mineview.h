/********************************************************************************
** Form generated from reading UI file 'mineview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINEVIEW_H
#define UI_MINEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mineview
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mineview)
    {
        if (mineview->objectName().isEmpty())
            mineview->setObjectName("mineview");
        mineview->resize(800, 600);
        centralwidget = new QWidget(mineview);
        centralwidget->setObjectName("centralwidget");
        mineview->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mineview);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        mineview->setMenuBar(menubar);
        statusbar = new QStatusBar(mineview);
        statusbar->setObjectName("statusbar");
        mineview->setStatusBar(statusbar);

        retranslateUi(mineview);

        QMetaObject::connectSlotsByName(mineview);
    } // setupUi

    void retranslateUi(QMainWindow *mineview)
    {
        mineview->setWindowTitle(QCoreApplication::translate("mineview", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mineview: public Ui_mineview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINEVIEW_H
