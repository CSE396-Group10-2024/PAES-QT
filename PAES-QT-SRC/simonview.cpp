#include "simonview.h"
#include <QKeyEvent>
#include <QApplication>
#include <QKeyEvent>
#include "games.h"

SimonView::SimonView(QWidget *parent)
    : QGraphicsView{parent}, m_gameScene(new SimonGameScene(this))
{
    setScene(m_gameScene);
    resize(sceneRect().width() + 2, sceneRect().height() + 2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(m_gameScene, &SimonGameScene::changePattern, m_gameScene, &SimonGameScene::setPattern);
    setCursor(QCursor(QPixmap(SimonGame::PATH_TO_CURSOR_PIXMAP)));

    backButton_s = new QPushButton("<-", this);
    backButton_s->setStyleSheet(
        "QPushButton {"
        "   color: black;"              // Ensure text color is black
        "   background-color: white;"   // Button background is white
        "   border-style: none;"        // No border for a flat look
        "   border: 1px solid #8f8f91;"
        "   border-radius: 7px;"
        "   padding: 5px 10px;"         // Adjust padding to match the visual weight
        "   font-size: 16px;"           // Ensure font size is sufficiently large
        "}"
        );

    // Set cursor to pointing hand when hovering over the button
    backButton_s->setCursor(Qt::PointingHandCursor);

    // Position the button to match the provided image layout
    backButton_s->setGeometry(10, 10, 35, 35);  // Adjust size to match the image

    connect(backButton_s, &QPushButton::clicked, this, &SimonView::handleBackButton_s); // Corrected connect statement

    // Ensure the button is always on top and doesn't move
    backButton_s->setFlat(true);
    backButton_s->raise(); // Bring the button to the front
    backButton_s->show();

}
void SimonView::handleBackButton_s(){
    //For example, just close this window
    if (backButton_s) {
        backButton_s->setEnabled(false);
    }
    Games* game2 = new Games();
    game2->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    game2->showMaximized();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();
    if (backButton_s) {
        backButton_s->setEnabled(true);
    }
}

void SimonView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
    QGraphicsView::keyPressEvent(event);
}
