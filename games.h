#ifndef GAMES_H
#define GAMES_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class Games;
}

class Games : public QMainWindow
{
    Q_OBJECT

public:
    explicit Games(QWidget *parent = nullptr);
    ~Games();

private slots:
    void on_gamebutton3_clicked();

    void on_gamebutton1_clicked();

    void on_gamebutton2_clicked();

    void on_returnToMain_clicked();

private:
    Ui::Games *ui;

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_F11) {
            toggleFullscreen();
        } else {
            QWidget::keyPressEvent(event); // Pass other key events to the base class
        }
    }

    void toggleFullscreen() {
        if (isFullScreen()) {
            showNormal(); // Exit fullscreen mode
        } else {
            showFullScreen(); // Enter fullscreen mode
        }
    }
};

#endif // GAMES_H
