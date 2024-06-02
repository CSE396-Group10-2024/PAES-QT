/********************************************************************************
** Form generated from reading UI file 'bejewview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEJEWVIEW_H
#define UI_BEJEWVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bejewview
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *bejewview)
    {
        if (bejewview->objectName().isEmpty())
            bejewview->setObjectName("bejewview");
        bejewview->resize(800, 600);
        centralwidget = new QWidget(bejewview);
        centralwidget->setObjectName("centralwidget");
        bejewview->setCentralWidget(centralwidget);
        menubar = new QMenuBar(bejewview);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        bejewview->setMenuBar(menubar);
        statusbar = new QStatusBar(bejewview);
        statusbar->setObjectName("statusbar");
        bejewview->setStatusBar(statusbar);

        retranslateUi(bejewview);

        QMetaObject::connectSlotsByName(bejewview);
    } // setupUi

    void retranslateUi(QMainWindow *bejewview)
    {
        bejewview->setWindowTitle(QCoreApplication::translate("bejewview", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bejewview: public Ui_bejewview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEJEWVIEW_H
