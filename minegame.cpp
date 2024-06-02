#include "minegame.h"

const QSize MineGame::RESOLUTION = QSize(800, 800); // Adjust the resolution if needed
const int GRID_SIZE = 20; // Set the desired grid size

MineGame::MineGame()
    : w(32), // Adjust the width of each grid cell accordingly
    PATH_TO_TILES(":/images/tiles.png"),
    PATH_TO_FACE(":/images/face.png"),
    ITERATION_VALUE(1000.0f / 60.0f)
{
    init();

}

void MineGame::init()
{
    srand(time(0));
    for (int i = 1; i <= GRID_SIZE; i++)
    {
        for (int j = 1; j <= GRID_SIZE; j++)
        {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0)
                grid[i][j] = 9;
            else
                grid[i][j] = 0;
        }
    }

    for (int i=1 ; i<=GRID_SIZE ; i++)
    {
        for (int j=1; j<=GRID_SIZE; j++)
        {
            int n=0;
            if (grid[i][j] == 9)
            {
                continue;
            }
            if (grid[i+1][j] == 9)
            {
                n++;
            }
            if (grid[i][j+1] == 9)
            {
                n++;
            }
            if (grid[i-1][j] == 9)
            {
                n++;
            }
            if (grid[i][j-1] == 9)
            {
                n++;
            }
            if (grid[i+1][j+1] == 9)
            {
                n++;
            }
            if (grid[i-1][j-1] == 9)
            {
                n++;
            }
            if (grid[i-1][j+1] == 9)
            {
                n++;
            }
            if (grid[i+1][j-1] == 9)
            {
                n++;
            }
            grid[i][j]=n;
        }
    }
}
