#ifndef MINEVIEW_H
#define MINEVIEW_H

#include <QGraphicsView>
#include <QPushButton>

class MineGameScene;

class MineView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MineView();
    void handleBackButton();

signals:
private:
    MineGameScene *m_gameScene;
    QPushButton* backButton_m;  // Button to go back
};

#endif // VIEW_H
