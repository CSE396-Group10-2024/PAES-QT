#ifndef MINEGAME_H
#define MINEGAME_H
#include <QSize>

class MineGame
{
public:
    MineGame();
    static const QSize RESOLUTION;
    const int w;
    const QString PATH_TO_TILES;
    const QString PATH_TO_FACE;
    int grid[22][22];
    int sgrid[22][22];
    const float ITERATION_VALUE;
    void init();
};

#endif // GAME_H
