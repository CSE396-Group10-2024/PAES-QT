// Header file: Worker.h
#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
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
#include <QThread>

class Worker : public QThread  {
    Q_OBJECT

public:
    void run()override;
    virtual void terminate();

    bool shouldStop = false; // Flag to control the loop
    void stopWork(){
        shouldStop = true;
    }

    int right_head_assigned_number;
    int right_head_repeated_number;
    int left_head_assigned_number;
    int left_head_repeated_number;
    int right_arm_assigned_number;
    int right_arm_repeated_number;
    int left_arm_assigned_number;
    int left_arm_repeated_number;
    int t_pose_assigned_number;
    int t_pose_repeated_number;
    int squat_assigned_number;
    int squat_repeated_number;
    int right_knee_assigned_number;
    int right_knee_repeated_number;
    int left_knee_assigned_number;
    int left_knee_repeated_number;
    int zombie_assigned_number;
    int zombie_repeated_number;


signals:
    void updateRightHeadProgress(float value, int rep);
    void updateLeftHeadProgress(float value, int rep);
    void updateRightArmProgress(float value, int rep);
    void updateLeftArmProgress(float value, int rep);

    void updateTposeProgress(float value, int rep);
    void updateSquatProgress(float value, int rep);
    void updateRightKneeProgress(float value, int rep);
    void updateLeftKneeProgress(float value, int rep);
    void updateZombieProgress(float value, int rep);

public slots:

private:



};




#endif // WORKER_H
