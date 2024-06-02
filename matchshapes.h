#ifndef MATCHSHAPES_H
#define MATCHSHAPES_H

#include <QMainWindow>
#include <draggablelabel.h>
#include <QPushButton>

namespace Ui {
class matchshapes;
}

class matchshapes : public QMainWindow
{
    Q_OBJECT

public:
    explicit matchshapes(QWidget *parent = nullptr);
    ~matchshapes();
    void handleBackButton_s();

private slots:
    void on_pushButton_clicked();

private:
    Ui::matchshapes *ui;
    QPushButton * backButton_s;
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

#endif // MATCHSHAPES_H
