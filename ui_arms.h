/********************************************************************************
** Form generated from reading UI file 'arms.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARMS_H
#define UI_ARMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_arms
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *arms)
    {
        if (arms->objectName().isEmpty())
            arms->setObjectName("arms");
        arms->resize(800, 600);
        centralwidget = new QWidget(arms);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);


        horizontalLayout_2->addLayout(horizontalLayout);

        arms->setCentralWidget(centralwidget);
        menubar = new QMenuBar(arms);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        arms->setMenuBar(menubar);
        statusbar = new QStatusBar(arms);
        statusbar->setObjectName("statusbar");
        arms->setStatusBar(statusbar);

        retranslateUi(arms);

        QMetaObject::connectSlotsByName(arms);
    } // setupUi

    void retranslateUi(QMainWindow *arms)
    {
        arms->setWindowTitle(QCoreApplication::translate("arms", "MainWindow", nullptr));
        pushButton_3->setText(QCoreApplication::translate("arms", "KOL EGZERS\304\260Z\304\260 1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("arms", "KOL EGZERS\304\260Z\304\260 2", nullptr));
        pushButton->setText(QCoreApplication::translate("arms", "KOL EGZERS\304\260Z\304\260 3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class arms: public Ui_arms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARMS_H
