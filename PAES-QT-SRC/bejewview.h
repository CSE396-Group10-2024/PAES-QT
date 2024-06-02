#ifndef BEJEWVIEW_H
#define BEJEWVIEW_H

#include <QGraphicsView>
#include "bejewgamescene.h"
#include <QPushButton>

class BejewView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BejewView();
    void handleBackButton_b();

signals:

private:
    BejewGameScene *m_gameScene;
    QPushButton* backButton_b;  // Button to go back
    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H

