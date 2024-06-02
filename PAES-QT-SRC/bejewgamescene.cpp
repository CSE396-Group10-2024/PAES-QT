#include "bejewgamescene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPainter>
#include <QDir>
#include <QDebug>
const int GRID_SIZE = 16;


BejewGameScene::BejewGameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_click(0), m_isSwap(false), m_isMoving(false), m_tmpScore(0)
    , m_deltaTime(0.f), m_animationTime(0.f), m_animationSpeed(20.f)
{
    loadPixmap();
    setSceneRect(0, 0, BejewGame::RESOLUTION.width(), BejewGame::RESOLUTION.height());
    setBackgroundBrush(QBrush(QColor(153, 255, 51)));
    init();
    draw();
    connect(&m_timer, &QTimer::timeout, this, &BejewGameScene::loop);
    m_timer.start(BejewGame::ITERATION_VALUE);
    m_elapsedTimer.start();
}

void BejewGameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_animationTime += m_deltaTime;

    if (m_animationTime > m_animationSpeed)
    {
        m_animationTime -= m_animationSpeed;
        mouseClick();
        matchFinding();
        movingAnimation();
        removeAnimation();
        updateScore();
        swapBackIfNotMatch();
        updateGrid();
        draw();
        drawScore();
    }
}

void BejewGameScene::loadPixmap()
{
    if(m_BgPixmap.load(BejewGame::PATH_TO_BG_PIXMAP))
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }

    if(m_GemsPixmap.load(BejewGame::PATH_TO_GEMS_PIXMAP))
    {
        qDebug() << "GemsPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "GemsPixmap is not loaded successfully";
    }

    if(m_framePixmap.load(BejewGame::PATH_TO_FRAME_PIXMAP))
    {
        qDebug() << "FramePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "FramePixmap is not loaded successfully";
    }

    if(m_scorePixmap.load(BejewGame::PATH_TO_SCORE_PIXMAP))
    {
        qDebug() << "ScorePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ScorePixmap is not loaded successfully";
    }

    if(m_numbersPixmap.load(BejewGame::PATH_TO_NUMBERS_PIXMAP))
    {
        qDebug() << "NumbersPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "NumbersPixmap is not loaded successfully";
    }
}

void BejewGameScene::init()
{
    clear();
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_BgPixmap.scaled(BejewGame::RESOLUTION.width(), BejewGame::RESOLUTION.height()));
    addItem(bgItem);

    QGraphicsPixmapItem *frameItem = new QGraphicsPixmapItem(m_framePixmap);
    frameItem->setPos(BejewGame::OFFSET.x() - 2, BejewGame::OFFSET.y());
    addItem(frameItem);

    for(int i = 0; i < 18; ++i)
    {
        for(int j = 0; j < 18; ++j)
        {
            addItem(&m_pixmapItems[i][j]);
        }
    }

    QGraphicsPixmapItem *scoreItem = new QGraphicsPixmapItem(m_scorePixmap);
    scoreItem->setPos(BejewGame::RESOLUTION.width() - scoreItem->boundingRect().width() - 85, 880);
    addItem(scoreItem);

    unityPartScoreItem.moveBy(BejewGame::RESOLUTION.width()-32, 880);
    addItem(&unityPartScoreItem);

    decimalPartScoreItem.moveBy(BejewGame::RESOLUTION.width()-2*32, 880);
    addItem(&decimalPartScoreItem);

    hundredthPartScoreItem.moveBy(BejewGame::RESOLUTION.width()-3*32, 880);
    addItem(&hundredthPartScoreItem);
}

void BejewGameScene::draw()
{
    for (int i=1;i<=GRID_SIZE;i++)
    {
        for (int j=1;j<=GRID_SIZE;j++)
        {
            Piece p = m_game.m_grid[i][j];
            QImage image = m_GemsPixmap.copy(p.kind*49, 0, 49, 49).toImage().convertToFormat(QImage::Format_ARGB32);
            //            for (int x(0); x != image.width(); ++x)
            //            {
            //                for (int y(0); y != image.height(); ++y)
            //                {
            //                    QColor color(image.pixel(x,y));
            //                    color.setAlpha(p.alpha);
            //                    image.setPixel(x, y, color.rgba());
            //                }
            //            }
            m_pixmapItems[i][j].setPixmap(QPixmap::fromImage(image));
            m_pixmapItems[i][j].setPos(p.x, p.y);
            m_pixmapItems[i][j].moveBy(BejewGame::OFFSET.x() - BejewGame::TILE_SIZE, BejewGame::OFFSET.y() - BejewGame::TILE_SIZE);

        }
    }
}

void BejewGameScene::mouseClick()
{
    if (m_click == 1)
    {
        m_x0 = m_pos.x() / BejewGame::TILE_SIZE+1;
        m_y0 = m_pos.y() / BejewGame::TILE_SIZE+1;
    }
    if (m_click == 2)
    {
        m_x = m_pos.x() / BejewGame::TILE_SIZE+1;
        m_y = m_pos.y() / BejewGame::TILE_SIZE+1;
        if ( abs(m_x-m_x0)+abs(m_y-m_y0)==1)
        {
            m_game.swap(m_game.m_grid[m_y0][m_x0],m_game.m_grid[m_y][m_x]);
            m_isSwap = true;
            m_click = 0;
        }
        else
        {
            m_click = 1;
        }
    }
}

void BejewGameScene::matchFinding()
{
    for(int i=1;i<=GRID_SIZE;i++)
    {
        for(int j=1;j<=GRID_SIZE;j++)
        {
            if (m_game.m_grid[i][j].kind == m_game.m_grid[i+1][j].kind)
            {
                if ( m_game.m_grid[i][j].kind == m_game.m_grid[i-1][j].kind)
                {
                    for(int n=-1;n<=1;n++)
                    {
                        m_game.m_grid[i+n][j].match += 1;
                    }
                }

            }


            if (m_game.m_grid[i][j].kind == m_game.m_grid[i][j+1].kind)
            {
                if (m_game.m_grid[i][j].kind == m_game.m_grid[i][j-1].kind)
                {
                    for(int n=-1;n<=1;n++)
                    {
                        m_game.m_grid[i][j+n].match += 1;
                    }
                }

            }
        }
    }
}

void BejewGameScene::movingAnimation()
{
    m_isMoving = false;
    for (int i = 1; i <= GRID_SIZE; i++)
    {
        for (int j = 1; j<=GRID_SIZE; j++)
        {
            Piece &p = m_game.m_grid[i][j];
            int dx,dy;
            for(int n=0;n<8;n++)   // 4 - speed
            {
                dx = p.x-p.col * BejewGame::TILE_SIZE;
                dy = p.y-p.row * BejewGame::TILE_SIZE;
                if (dx)
                {
                    p.x-=dx/abs(dx);
                }
                if (dy)
                {
                    p.y-=dy/abs(dy);
                }
            }
            if (dx||dy)
            {
                m_isMoving = true;
            }
        }
    }
}

void BejewGameScene::removeAnimation()
{
    if (!m_isMoving)
    {
        for (int i=1;i<=GRID_SIZE;i++)
        {
            for (int j=1;j<=GRID_SIZE;j++)
            {
                if (m_game.m_grid[i][j].match)
                {
                    if (m_game.m_grid[i][j].alpha>10)
                    {
                        m_game.m_grid[i][j].alpha -= 10;
                        m_isMoving = true;
                    }
                }
            }
        }
    }

}

void BejewGameScene::updateScore()
{
    m_tmpScore = 0;
    for (int i=1;i<=GRID_SIZE;i++)
    {
        for (int j=1;j<=GRID_SIZE;j++)
        {
            m_tmpScore += m_game.m_grid[i][j].match;
        }
    }

}

void BejewGameScene::swapBackIfNotMatch()
{
    if (m_isSwap && !m_isMoving)
    {
        if (!m_tmpScore)
        {
            m_game.swap(m_game.m_grid[m_y0][m_x0],m_game.m_grid[m_y][m_x]);
        }
        m_isSwap = false;
    }

}

void BejewGameScene::updateGrid()
{
    if (!m_isMoving)
    {
        for(int i=GRID_SIZE;i>0;i--)
        {
            for(int j=1;j<=GRID_SIZE;j++)
            {
                if (m_game.m_grid[i][j].match)
                {
                    for(int n=i;n>0;n--)
                    {
                        if (!m_game.m_grid[n][j].match)
                        {
                            m_game.swap(m_game.m_grid[n][j], m_game.m_grid[i][j]);

                            m_game.m_score++;

                            break;
                        }
                    }
                }
            }
        }


        for(int j=1;j<=GRID_SIZE;j++)
        {
            for(int i=GRID_SIZE,n=0;i>0;i--)
            {
                if (m_game.m_grid[i][j].match)
                {
                    m_game.m_grid[i][j].kind = rand()%7;
                    m_game.m_grid[i][j].y = -BejewGame::TILE_SIZE*n++;
                    m_game.m_grid[i][j].match=0;
                    m_game.m_grid[i][j].alpha = 255;
                }
            }
        }

    }
}

void BejewGameScene::removePixmapItems()
{
    for(int i = 0; i < 18; ++i)
    {
        for(int j =0; j < 18; ++j)
        {
            removeItem(&m_pixmapItems[i][j]);
        }
    }
}

void BejewGameScene::drawScore()
{
    QString scoreText = QString::number(m_game.m_score);
    int unityPartVal = 0;
    int decimalPartValue = 0;
    int hendredthPartValue = 0;

    if(scoreText.length() == 1) // 0 - 9
    {
        unityPartVal = scoreText.toInt();
        decimalPartValue = 0;
        hendredthPartValue = 0;
    }
    else if(scoreText.length() == 2) // 10 - 99
    {
        unityPartVal = scoreText.last(1).toInt();
        decimalPartValue = scoreText.first(1).toInt();
        hendredthPartValue = 0;
    }
    else if(scoreText.length() == 3) // 100 - 999
    {
        unityPartVal = scoreText.last(1).toInt();
        hendredthPartValue = scoreText.first(1).toInt();
        QString copyVal = scoreText;
        copyVal.chop(1);
        decimalPartValue = copyVal.last(1).toInt();
    }

    unityPartScoreItem.setPixmap(m_numbersPixmap.copy(unityPartVal*32, 0, 32, 32));
    decimalPartScoreItem.setPixmap(m_numbersPixmap.copy(decimalPartValue*32, 0, 32, 32));
    hundredthPartScoreItem.setPixmap(m_numbersPixmap.copy(hendredthPartValue*32, 0, 32, 32));
}

void BejewGameScene::renderScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

void BejewGameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if (!m_isSwap && !m_isMoving)
        {
            m_click++;
        }
        m_pos = QPoint(event->scenePos().x(), event->scenePos().y()) - BejewGame::OFFSET;
    }
}

void BejewGameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Z:
    {
        //renderScene();
    }
    break;
    }

    QGraphicsScene::keyPressEvent(event);
}
