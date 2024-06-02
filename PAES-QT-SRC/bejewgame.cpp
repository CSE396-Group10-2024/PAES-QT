#include "bejewgame.h"

const QSize BejewGame::RESOLUTION = QSize(862, 940);
const QPoint BejewGame::OFFSET = QPoint(0,0);
const int BejewGame::TILE_SIZE = 54;
const QString BejewGame::PATH_TO_BG_PIXMAP = ":/images/background.png";
const QString BejewGame::PATH_TO_GEMS_PIXMAP = ":/images/gems.png";
const float BejewGame::ITERATION_VALUE = 1000.0f/60.0f;
const QString BejewGame::PATH_TO_FRAME_PIXMAP = ":/images/frame.png";
const QString BejewGame::PATH_TO_SCORE_PIXMAP = ":/images/score.png";
const QString BejewGame::PATH_TO_CURSOR_PIXMAP = ":/images/cursor.png";
const QString BejewGame::PATH_TO_NUMBERS_PIXMAP = ":/images/numbers.png";
const int GRID_SIZE = 16;

BejewGame::BejewGame()
    : m_score(0)
{
    initGrid();
}

void BejewGame::swap(Piece p1,Piece p2)
{
    std::swap(p1.col,p2.col);
    std::swap(p1.row,p2.row);

    m_grid[p1.row][p1.col]=p1;
    m_grid[p2.row][p2.col]=p2;
}

void BejewGame::initGrid()
{
    srand(time(0));
    for (int i=1;i<=GRID_SIZE;i++)
    {
        for (int j=1;j<=GRID_SIZE;j++)
        {
            m_grid[i][j].kind = rand()%7;
            m_grid[i][j].col = j;
            m_grid[i][j].row = i;
            m_grid[i][j].x = j * TILE_SIZE;
            m_grid[i][j].y = i * TILE_SIZE;
        }
    }
}
