/********************************************************************************
** Form generated from reading UI file 'shoulders.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOULDERS_H
#define UI_SHOULDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_shoulders
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *shoulders)
    {
        if (shoulders->objectName().isEmpty())
            shoulders->setObjectName("shoulders");
        shoulders->resize(800, 600);
        centralwidget = new QWidget(shoulders);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
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

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_4);


        horizontalLayout_2->addLayout(horizontalLayout);

        shoulders->setCentralWidget(centralwidget);
        menubar = new QMenuBar(shoulders);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        shoulders->setMenuBar(menubar);
        statusbar = new QStatusBar(shoulders);
        statusbar->setObjectName("statusbar");
        shoulders->setStatusBar(statusbar);

        retranslateUi(shoulders);

        QMetaObject::connectSlotsByName(shoulders);
    } // setupUi

    void retranslateUi(QMainWindow *shoulders)
    {
        shoulders->setWindowTitle(QCoreApplication::translate("shoulders", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("shoulders", "Omuz Egzersizi 1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("shoulders", "Omuz Egzersizi 2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("shoulders", "Omuz Egzersizi 3", nullptr));
        pushButton_4->setText(QCoreApplication::translate("shoulders", "Omuz Egzersizi 4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shoulders: public Ui_shoulders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOULDERS_H
