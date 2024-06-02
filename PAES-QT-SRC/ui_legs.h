/********************************************************************************
** Form generated from reading UI file 'legs.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEGS_H
#define UI_LEGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_legs
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *legs)
    {
        if (legs->objectName().isEmpty())
            legs->setObjectName("legs");
        legs->resize(800, 600);
        centralwidget = new QWidget(legs);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);


        horizontalLayout_2->addLayout(horizontalLayout);

        legs->setCentralWidget(centralwidget);
        menubar = new QMenuBar(legs);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        legs->setMenuBar(menubar);
        statusbar = new QStatusBar(legs);
        statusbar->setObjectName("statusbar");
        legs->setStatusBar(statusbar);

        retranslateUi(legs);

        QMetaObject::connectSlotsByName(legs);
    } // setupUi

    void retranslateUi(QMainWindow *legs)
    {
        legs->setWindowTitle(QCoreApplication::translate("legs", "MainWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("legs", "Bacak Egzersizi 1", nullptr));
        pushButton->setText(QCoreApplication::translate("legs", "Bacak Egzersizi 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class legs: public Ui_legs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEGS_H
