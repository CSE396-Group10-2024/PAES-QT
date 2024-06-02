#include "bejewview.h"
#include <QKeyEvent>
#include <QApplication>
#include "mainwindow.h"

BejewView::BejewView()
    : QGraphicsView(), m_gameScene(new BejewGameScene(this))
{
    setScene(m_gameScene);
    resize(m_gameScene->sceneRect().width() + 2, m_gameScene->sceneRect().height() + 2);
    setCursor(QCursor(QPixmap(":/images/cursor.png")));
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    backButton_b = new QPushButton("<-", this);
    backButton_b->setStyleSheet(
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
    backButton_b->setCursor(Qt::PointingHandCursor);

// Position the button to match the provided image layout
    backButton_b->setGeometry(10, 10, 35, 35);  // Adjust size to match the image

    connect(backButton_b, &QPushButton::clicked, this, &BejewView::handleBackButton_b); // Corrected connect statement

// Ensure the button is always on top and doesn't move
    backButton_b->setFlat(true);
    backButton_b->raise(); // Bring the button to the front
    backButton_b->show();

}

void BejewView::handleBackButton_b(){
    if (backButton_b) {
        backButton_b->setEnabled(false);
    }


    Games* game2 = new Games();
    game2->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    game2->showMaximized();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();

    if (backButton_b) {
        backButton_b->setEnabled(true);
    }

}


void BejewView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
    {
        QApplication::instance()->quit();
    }
    break;
    }
    QGraphicsView::keyPressEvent(event);
}

