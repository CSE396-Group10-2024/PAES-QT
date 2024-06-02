#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <games.h>
#include <QKeyEvent>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void startPythonServer(const QString& ip);
    void handleStandardOutput();
    void handleStandardError();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    Games *game;
    void terminatePythonServer();
    QProcess *process;  // Add QProcess as a member

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

#endif // MAINWINDOW_H
