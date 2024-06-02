#ifndef CANVAS_H
#define CANVAS_H

#include <QList>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>

// ScribbleArea used to paint the image
class ScribbleArea;

class Canvas : public QMainWindow
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT

public:
    Canvas();

protected:
    // Function used to close an event
    void closeEvent(QCloseEvent *event) override;

    // The events that can be triggered
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();
    void handleBackButton();

public slots:
    void savePng();

private:
    // Will tie user actions to functions
    void createActions();
    void createMenus();

    // Will check if changes have occurred since last save
    bool maybeSave();

    // Opens the Save dialog and saves
    bool saveFile(const QByteArray &fileFormat);

    // What we'll draw on
    ScribbleArea *scribbleArea;

    // The menu widgets
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    // All the actions that can occur
    QAction *openAct;

    // Actions tied to specific file formats
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_F11) {
            toggleFullscreen();
        }  else {
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

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            // Right mouse button was pressed
            savePng();
        }
        else{
        // Call base class implementation
            QWidget::mousePressEvent(event);
        }
    }


};

#endif
