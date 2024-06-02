#include "simongame.h"
#include <QString>
#include <QColor>

QColor SimonGame::BGCOLOR = BLACK;
const QString SimonGame::PATH_TO_BEEP_SOUNDS[4] =
    {
        QString("qrc:/res/beep1.wav"),
        QString("qrc:/res/beep2.wav"),
        QString("qrc:/res/beep3.wav"),
        QString("qrc:/res/beep4.wav")
};

const QString SimonGame::PATH_TO_BASIC_FONT = QString(":/res/freesansbold.ttf");
const QString SimonGame::PATH_TO_CURSOR_PIXMAP = QString(":/res/cursor.png");;
const QString SimonGame::GREEN_STR = "GREEN";
const QString SimonGame::RED_STR = "RED";
const QString SimonGame::YELLOW_STR = "YELLOW";
const QString SimonGame::BLUE_STR = "BLUE";
const QString SimonGame::INVALID_STR = "NONE";

SimonGame::SimonGame()
{

}
