#ifndef EXERCISES_H
#define EXERCISES_H

#include <QMainWindow>
#include <QKeyEvent>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <typeinfo>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <filesystem>
#include <string>
#include <iostream>
#include <cstring>
#include <csignal>
#include <unordered_map>
#include <QProcess>


namespace Ui {
class exercises;
}

class exercises : public QMainWindow
{
    Q_OBJECT

public:
    explicit exercises(QWidget *parent = nullptr);
    ~exercises();
    void closeEvent(QCloseEvent *event)override;
    std::string Expected_Move = "debug";
    // Handle standard output from the Python server
    void handleStandardOutput();
    // Handle standard error from the Python server
    void handleStandardError();
    void handleBackButton_s();

signals:
    void operatePythonProcess(const QString &command, const QStringList &arguments);
    void operateCppProcess(const QString &path);
    void terminateProcesses();
    void serverOperation(int port);
    void finishedServer();
    void terminateThread();
    void exitWhile();
    void stopWork();



private slots:
    void updateRightHeadProgressBar(int value ,int rep);
    void updateLeftHeadProgressBar(int value,int rep);
    void updateLeftArmProgressBar(int value,int rep);
    void updateRightArmProgressBar(int value ,int rep);

    void updateTposeProgressBar(int value,int rep );
    void updateSquatProgressBar(int value,int rep);
    void updateRightKneeProgressBar(int value,int rep);
    void updateLeftKneeProgressBar(int value,int rep);
    void updateZombieProgressBar(int value,int rep);

    void terminateServerThread();
    void startServerThread();

    void on_neck_right_clicked();
    void on_pushButton_clicked();
    void startPythonProcess(const QString &command, const QStringList &arguments);
    void startCppProcess(const QString &path);
    void stopProcesses();



    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    Ui::exercises *ui;
    QProcess * process_py = nullptr;
    QProcess * process_cpp = nullptr;


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




#endif // EXERCISES_H
