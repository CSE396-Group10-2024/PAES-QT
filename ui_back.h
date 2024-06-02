/********************************************************************************
** Form generated from reading UI file 'back.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACK_H
#define UI_BACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_back
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *back)
    {
        if (back->objectName().isEmpty())
            back->setObjectName("back");
        back->resize(800, 600);
        centralwidget = new QWidget(back);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        back->setCentralWidget(centralwidget);
        menubar = new QMenuBar(back);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        back->setMenuBar(menubar);
        statusbar = new QStatusBar(back);
        statusbar->setObjectName("statusbar");
        back->setStatusBar(statusbar);

        retranslateUi(back);

        QMetaObject::connectSlotsByName(back);
    } // setupUi

    void retranslateUi(QMainWindow *back)
    {
        back->setWindowTitle(QCoreApplication::translate("back", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("back", "S\304\261rt Egzersizi 2", nullptr));
        pushButton_2->setText(QCoreApplication::translate("back", "S\304\261rt Egzersizi 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class back: public Ui_back {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACK_H
