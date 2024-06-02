#include "mineview.h"
#include "minegame.h"
#include "minegamescene.h"
#include "mainwindow.h"
#include <QApplication>


MineView::MineView()
    : QGraphicsView(), m_gameScene(new MineGameScene(this))
{
    resize(MineGame::RESOLUTION.width()+2, MineGame::RESOLUTION.height()+2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_gameScene);

    backButton_m = new QPushButton("<-", this);
    backButton_m->setStyleSheet(
        "QPushButton {"
        "   color: black;"              // Ensure text color is black
        "   background-color: white;"   // Button background is white
        "   border-style: none;"        // No border for a flat look
        "   border: 1px solid #8f8f91;"
         "   border-radius: 10px;"
        "   padding: 5px 10px;"         // Adjust padding to match the visual weight
        "   font-size: 16px;"           // Ensure font size is sufficiently large
        "}"
        );

    // Set cursor to pointing hand when hovering over the button
    backButton_m->setCursor(Qt::PointingHandCursor);

    // Position the button to match the provided image layout
    backButton_m->setGeometry(10, 10, 35, 35);  // Adjust size to match the image

   connect(backButton_m, &QPushButton::clicked, this, &MineView::handleBackButton); // Corrected connect statement

    // Ensure the button is always on top and doesn't move
    backButton_m->setFlat(true);
    backButton_m->raise(); // Bring the button to the front
    backButton_m->show();

}

void MineView::handleBackButton()
{
    if (backButton_m) {
        backButton_m->setEnabled(false);
    }

    Games* game2 = new Games();
    game2->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    game2->showMaximized();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();

    // Then hide the current window
    if (backButton_m) {
        backButton_m->setEnabled(true);
    }

}
