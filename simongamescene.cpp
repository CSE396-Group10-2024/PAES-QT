#include "simongamescene.h"
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QThread>

SimonGameScene::SimonGameScene(QObject *parent)
    : QGraphicsScene(parent), m_deltaTime(0.0f), m_loopTime(0.0f),
    m_loopSpeed(1.0f/float(SimonGame::FPS)), m_score(0), m_waitingForInput(false), m_clickedPoint(SimonGame::INVALID_STR),
    MOVE_PATTERN{SimonGame::YELLOW_STR, SimonGame::RED_STR, SimonGame::BLUE_STR, SimonGame::GREEN_STR}
{
    setSceneRect(0,0, SimonGame::RESOLUTION.width(), SimonGame::RESOLUTION.height());
    // connect(&m_timer, &QTimer::timeout, this, &SimonGameScene::loop);
    m_timer.start(m_loopSpeed);
    m_elapsedTimer.start();

    srand(time(0));
    int id = QFontDatabase::addApplicationFont(SimonGame::PATH_TO_BASIC_FONT);
    m_basicFont = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 15, 0);
    m_pattern.clear();

    setBackgroundBrush(QBrush(SimonGame::BGCOLOR));
    drawInfoText();
    drawScoreText();
    drawButtons();
    drawStatusText();

    connect(this, &SimonGameScene::changePattern, this, &SimonGameScene::setPattern);
    connect(m_yellowRectItem, &RectItem::finishAlphaAnim, this, &SimonGameScene::nextPossibleAnim);
    connect(m_blueRectItem, &RectItem::finishAlphaAnim, this, &SimonGameScene::nextPossibleAnim);
    connect(m_redRectItem, &RectItem::finishAlphaAnim, this, &SimonGameScene::nextPossibleAnim);
    connect(m_greenRectItem, &RectItem::finishAlphaAnim, this, &SimonGameScene::nextPossibleAnim);

    m_currentAnim = 0;
    m_currentStep = 0;
    setPattern();
}

void SimonGameScene::loop()
{
}

void SimonGameScene::nextPossibleAnim()
{
    m_currentAnim++;
    if(m_currentAnim >= m_pattern.size())
    {
        m_waitingForInput = true;
        m_currentAnim = 0;
    }
    else
    {
        flashButtonAnimation(m_pattern[m_currentAnim]);
    }
}

void SimonGameScene::drawInfoText()
{
    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem();
    text->setFont(m_basicFont);
    text->setPos(10, SimonGame::RESOLUTION.height()-25);
    text->setPen(QPen(SimonGame::DARKGRAY));
    text->setBrush(QBrush(SimonGame::DARKGRAY));
    text->setText("                  Örüntüyü tıklayarak tekrardan oluşturun.");
    addItem(text);
}

void SimonGameScene::drawScoreText()
{
    m_scoreText = new QGraphicsSimpleTextItem();
    m_scoreText->setFont(m_basicFont);
    m_scoreText->setPos(SimonGame::RESOLUTION.width() - 100, 10);
    m_scoreText->setPen(QPen(SimonGame::WHITE));
    m_scoreText->setBrush(QBrush(SimonGame::WHITE));
    m_scoreText->setText("Score: " + QString::number(m_score));
    m_scoreText->setZValue(1);
    addItem(m_scoreText);
}

void SimonGameScene::drawStatusText()
{
    m_statusText = new QGraphicsSimpleTextItem();
    m_statusText->setFont(m_basicFont);
    m_statusText->setPos(0, 10);
    m_statusText->setPen(QPen(SimonGame::WHITE));
    m_statusText->setBrush(QBrush(SimonGame::WHITE));
    m_statusText->setText("Move: " + QString::number(m_currentStep).left(4) + " / " + QString::number(m_pattern.size()).left(4));
    addItem(m_statusText);
}

void SimonGameScene::drawButtons()
{
    m_yellowRectItem = new RectItem(SimonGame::PATH_TO_BEEP_SOUNDS[0]);
    m_yellowRectItem->setBrush(QBrush(SimonGame::YELLOW));
    m_yellowRectItem->setPen(QPen(SimonGame::YELLOW));
    m_yellowRectItem->setRect(0,0, SimonGame::YELLOWRECT.width(), SimonGame::YELLOWRECT.height());
    m_yellowRectItem->setPos(SimonGame::YELLOWRECT.x(), SimonGame::YELLOWRECT.y());
    addItem(m_yellowRectItem);

    m_blueRectItem = new RectItem(SimonGame::PATH_TO_BEEP_SOUNDS[1]);
    m_blueRectItem->setBrush(QBrush(SimonGame::BLUE));
    m_blueRectItem->setPen(QPen(SimonGame::BLUE));
    m_blueRectItem->setRect(0,0, SimonGame::BLUERECT.width(), SimonGame::BLUERECT.height());
    m_blueRectItem->setPos(SimonGame::BLUERECT.x(), SimonGame::BLUERECT.y());
    addItem(m_blueRectItem);

    m_redRectItem = new RectItem(SimonGame::PATH_TO_BEEP_SOUNDS[2]);
    m_redRectItem->setBrush(QBrush(SimonGame::RED));
    m_redRectItem->setPen(QPen(SimonGame::RED));
    m_redRectItem->setRect(0,0, SimonGame::REDRECT.width(), SimonGame::REDRECT.height());
    m_redRectItem->setPos(SimonGame::REDRECT.x(), SimonGame::REDRECT.y());
    addItem(m_redRectItem);

    m_greenRectItem = new RectItem(SimonGame::PATH_TO_BEEP_SOUNDS[3]);
    m_greenRectItem->setBrush(QBrush(SimonGame::GREEN));
    m_greenRectItem->setPen(QPen(SimonGame::GREEN));
    m_greenRectItem->setRect(0,0, SimonGame::GREENRECT.width(), SimonGame::GREENRECT.height());
    m_greenRectItem->setPos(SimonGame::GREENRECT.x(), SimonGame::GREENRECT.y());
    addItem(m_greenRectItem);

}

void SimonGameScene::changeBackgroundColor()
{
    setBackgroundBrush(QBrush(QColor(rand()%200, rand()%200, rand()%200)));
}

QString SimonGameScene::getButtonClicked(QPointF clickedPoint)
{
    if(SimonGame::YELLOWRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = SimonGame::YELLOW_STR;
        return m_clickedPoint;
    }
    else if(SimonGame::BLUERECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = SimonGame::BLUE_STR;
        return m_clickedPoint;
    }
    else if(SimonGame::REDRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = SimonGame::RED_STR;
        return m_clickedPoint;
    }
    else if(SimonGame::GREENRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = SimonGame::GREEN_STR;
        return m_clickedPoint;
    }

    return SimonGame::INVALID_STR;
}

void SimonGameScene::flashButtonAnimation(QString color)
{
    if(color == SimonGame::YELLOW_STR)
    {
        m_yellowRectItem->startAnim();
    }
    else if(color == SimonGame::BLUE_STR)
    {
        m_blueRectItem->startAnim();
    }
    else if(color == SimonGame::RED_STR)
    {
        m_redRectItem->startAnim();
    }
    else if(color == SimonGame::GREEN_STR)
    {
        m_greenRectItem->startAnim();
    }
}

void SimonGameScene::activeGameOver()
{
    m_waitingForInput = false;
    m_pattern.clear();
    m_score = 0;
    m_currentStep = 0;
    m_yellowRectItem->play();
    m_redRectItem->play();
    m_redRectItem->play();
    m_blueRectItem->play();
    setPattern();
    setBackgroundBrush(QBrush(SimonGame::BGCOLOR));
}

void SimonGameScene::checkClickedPosition()
{
    if(m_clickedPoint == m_pattern[m_currentStep])
    {
        m_currentStep++;
    }
    else
    {
        activeGameOver();
    }


    if(m_currentStep == m_pattern.size())
    {
        m_waitingForInput = false;
        setPattern();
        m_score++;
        m_currentStep = 0;
        changeBackgroundColor();
    }
    m_scoreText->setText("Score: " + QString::number(m_score));
    m_statusText->setText("Move: " + QString::number(m_currentStep).left(4) + " / " + QString::number(m_pattern.size()).left(4));
}

void SimonGameScene::setPattern()
{
    if(!m_waitingForInput)
    {
        QThread::currentThread()->msleep(1000);
        m_pattern.append(MOVE_PATTERN[rand() % SimonGame::PATTERN_SIZE]);
        m_statusText->setText("Move: " + QString::number(m_currentStep).left(4) + " / " + QString::number(m_pattern.size()).left(4));
        flashButtonAnimation(m_pattern[0]);
    }
}

void SimonGameScene::keyPressEvent(QKeyEvent *event)
{
    if(m_waitingForInput)
    {
        switch (event->key()) {
        case Qt::Key_Q:
            m_clickedPoint = SimonGame::YELLOW_STR;
            break;
        case Qt::Key_W:
            m_clickedPoint = SimonGame::BLUE_STR;
            break;
        case Qt::Key_A:
            m_clickedPoint = SimonGame::RED_STR;
            break;
        case Qt::Key_S:
            m_clickedPoint = SimonGame::GREEN_STR;
            break;
        }
        checkClickedPosition();
    }
    QGraphicsScene::keyPressEvent(event);
}

void SimonGameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_waitingForInput)
    {
        if(getButtonClicked(event->scenePos()) != SimonGame::INVALID_STR)
        {
            checkClickedPosition();
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
