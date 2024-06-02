#ifndef SIMONVIEW_H
#define SIMONVIEW_H

#include <QPushButton>
#include <QGraphicsView>
#include "simongamescene.h"

class SimonView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SimonView(QWidget *parent = nullptr);
    void handleBackButton_s();

signals:

private:
    SimonGameScene *m_gameScene;
    QPushButton* backButton_s;  // Button to go back
    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif
