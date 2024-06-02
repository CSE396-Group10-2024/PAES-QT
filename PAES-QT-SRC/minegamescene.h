#ifndef MINEGAMESCENE_H
#define MINEGAMESCENE_H

#include <QGraphicsScene>
#include "minegame.h"

class QTimer;
class MineGameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MineGameScene(QObject *parent = nullptr);

signals:

private slots:
    void update();
private:
    void loadPixmap();
    void checkResetClick(int x, int y);
    void floodFill(int x, int y);
    MineGame m_game;
    QPixmap m_tilesPixmap;
    QPixmap m_facePixmap;
    QTimer *m_timer;
    int m_x, m_y;
    bool m_resetVal;
    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
