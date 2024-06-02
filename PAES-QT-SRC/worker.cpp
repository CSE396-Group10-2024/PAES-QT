#include "worker.h"
#include "QThread"
#include "userinfo.h"

using namespace std;

int w_serverSocket = -1;
int w_clientSocket = -1;
int w_port = 1235;

void Worker::terminate(){
    shouldStop = true;
}

void Worker::run() {

    auto patient_data = UserInfo::getInstance()->getPatientData();
    bsoncxx::document::view pData = patient_data.view();
    auto todays_exercises = pData["todays_exercises"].get_document().value;

    auto right_head = todays_exercises["right_head"].get_document().value;
    right_head_assigned_number = right_head["assigned_number"].get_int32().value;
    right_head_repeated_number = right_head["repeated_number"].get_int32().value;

    auto left_head = todays_exercises["left_head"].get_document().value;
    left_head_assigned_number = left_head["assigned_number"].get_int32().value;
    left_head_repeated_number = left_head["repeated_number"].get_int32().value;

    auto left_arm = todays_exercises["left_arm"].get_document().value;
    left_arm_assigned_number = left_arm["assigned_number"].get_int32().value;
    left_arm_repeated_number = left_arm["repeated_number"].get_int32().value;;


    auto right_arm = todays_exercises["right_arm"].get_document().value;
    right_arm_assigned_number = right_arm["assigned_number"].get_int32().value;
    right_arm_repeated_number = right_arm["repeated_number"].get_int32().value;

    auto t_pose = todays_exercises["t_pose"].get_document().value;
    t_pose_assigned_number = t_pose["assigned_number"].get_int32().value;
    t_pose_repeated_number = t_pose["repeated_number"].get_int32().value;

    auto squat = todays_exercises["squat"].get_document().value;
    squat_assigned_number = squat["assigned_number"].get_int32().value;
    squat_repeated_number = squat["repeated_number"].get_int32().value;

    auto right_knee = todays_exercises["right_knee"].get_document().value;
    right_knee_assigned_number = right_knee["assigned_number"].get_int32().value;
    right_knee_repeated_number = right_knee["repeated_number"].get_int32().value;

    auto left_knee = todays_exercises["left_knee"].get_document().value;
    left_knee_assigned_number = left_knee["assigned_number"].get_int32().value;
    left_knee_repeated_number = left_knee["repeated_number"].get_int32().value;

    auto zombie = todays_exercises["zombie"].get_document().value;
    zombie_assigned_number = zombie["assigned_number"].get_int32().value;
    zombie_repeated_number = zombie["repeated_number"].get_int32().value;

    qDebug() << "Before beginning doing exercises here are the values: \n";
    qDebug() << "right_head_assigned_number: " <<right_head_assigned_number << "\n";
    qDebug() << "right_head_repeated_number: " <<right_head_repeated_number << "\n";

    qDebug() << "left_head_assigned_number: " <<left_head_assigned_number << "\n";
    qDebug() << "left_head_repeated_number: " <<left_head_repeated_number << "\n";

    qDebug() << "left_arm_assigned_number: " <<left_arm_assigned_number << "\n";
    qDebug() << "left_arm_repeated_number: " <<left_arm_repeated_number << "\n";

    qDebug() << "right_arm_assigned_number: " <<right_arm_assigned_number << "\n";
    qDebug() << "right_arm_repeated_number: " <<right_arm_repeated_number << "\n";

    qDebug() << "t_pose_assigned_number: " <<t_pose_assigned_number << "\n";
    qDebug() << "t_pose_repeated_number: " <<t_pose_repeated_number << "\n";

    qDebug() << "squat_assigned_number: " <<squat_assigned_number << "\n";
    qDebug() << "squat_repeated_number: " <<squat_repeated_number << "\n";

    qDebug() << "right_knee_assigned_number: " <<right_knee_assigned_number << "\n";
    qDebug() << "right_knee_repeated_number: " <<right_knee_repeated_number << "\n";

    qDebug() << "left_knee_assigned_number: " <<left_knee_assigned_number << "\n";
    qDebug() << "left_knee_repeated_number: " <<left_knee_repeated_number << "\n";

    qDebug() << "zombie_assigned_number: " <<zombie_assigned_number << "\n";
    qDebug() << "zombie_repeated_number: " <<zombie_repeated_number << "\n";

    char move_name[50];
    float probability;
    char status[50];
    int repetition;

    w_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (w_serverSocket == -1) {
        cerr<<"socket creation error "<<strerror(errno) <<endl;
    }
    int enable=1;
    if (setsockopt(w_serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        cerr<<"stsockopt(SO_REUSEADDR) failed"<<endl;


    // Set up server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr =  htonl(INADDR_ANY); // Replace with desired w_port
    serverAddress.sin_port = htons(w_port);

    // Bind the socket
    if (bind(w_serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {

        cout<<"binding error:"<< strerror(errno) <<endl;
    }

    // Listen for connections
    if (listen(w_serverSocket, 1) == -1) {
        cout<<"listen error "<<strerror(errno) <<endl;

        // Handle error
    }

    std::cout << "FROM QT: Server listening on w_port ..." << std::endl;

    // Accept a connection
    sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    if ((w_clientSocket = accept(w_serverSocket, (sockaddr*)&clientAddress, &clientAddressSize)) == -1) {
        std::cerr << "FROM QT: Client socket error: " << strerror(errno) << std::endl;
    }

    //sleep(2);

    std::cout << "FROM QT: Client connected from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << std::endl;

    while (true){
        char buffer[1024];
        memset(buffer, 0, 1024);

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(w_clientSocket, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 0.5;
        timeout.tv_usec = 0;

        int activity = select(w_clientSocket + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            std::cerr << "Select error: " << strerror(errno) << std::endl;
        } else if (activity == 0) {
            std::cout << "Timeout: connect No data received for " << 0.5 << " seconds." << std::endl;
        }
        else{
            ssize_t bytesReceived = recv(w_clientSocket, buffer, 1024 - 1, 0);
            if (bytesReceived < 0) {
                std::cerr << "Error receiving message: " << strerror(errno) << std::endl;
            } else if (bytesReceived == 0) {
                std::cout << "Client disconnected." << std::endl;
            }
            std::cout << "From pose: Received echo: " << buffer << std::endl;

            if(strncmp(buffer,"Connection established from client.",1024)==0){
                qDebug() << "AISJDOIANOISDNIAONSDNAOSDMNIASDAMNSKDLALSMDNKLASNDKLANKLDSNAKLSDNKLASNDLKADNS\n";
                break;
            }
        }
    }

    int debug = 0;
    while(!shouldStop){

        if(w_clientSocket != -1){

            char buffer[1024];
            memset(buffer, 0, 1024);

            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(w_clientSocket, &readfds);
            float timeout_sec=0.2;
            struct timeval timeout;
            timeout.tv_sec =timeout_sec;
            timeout.tv_usec = timeout_sec*1000000;

            int activity = select(w_clientSocket + 1, &readfds, NULL, NULL, &timeout);

            if (activity < 0) {
                qDebug() << "Select error: " << strerror(errno) << "\n";
            }
            else if (activity == 0) {
                qDebug() << "Timeout: hadaaa No data received for " << 0.5 << " seconds." << "\n";
            }
            else{
                ssize_t bytesReceived = recv(w_clientSocket, buffer, 1024 - 1, 0);
                if (bytesReceived < 0) {
                    qDebug() << "Error receiving message: " << strerror(errno) <<  "\n";
                }
                else if (bytesReceived == 0) {
                    qDebug() << "Echo can not received.";
                }
                else{
                    //where to process message and do all work
                    if(strncmp(buffer,"EXIT",1024)==0) {
                        qDebug()<<buffer<<"\n";
                        qDebug()<<"Break from while";
                        close(w_clientSocket);
                        close(w_serverSocket);


                        qDebug() << "AFTER COMPELETING EXERCISES: \n";
                        qDebug() << "right_head_assigned_number: " <<right_head_assigned_number << "\n";
                        qDebug() << "right_head_repeated_number: " <<right_head_repeated_number << "\n";

                        qDebug() << "left_head_assigned_number: " <<left_head_assigned_number << "\n";
                        qDebug() << "left_head_repeated_number: " <<left_head_repeated_number << "\n";

                        qDebug() << "left_arm_assigned_number: " <<left_arm_assigned_number << "\n";
                        qDebug() << "left_arm_repeated_number: " <<left_arm_repeated_number << "\n";

                        qDebug() << "right_arm_assigned_number: " <<right_arm_assigned_number << "\n";
                        qDebug() << "right_arm_repeated_number: " <<right_arm_repeated_number << "\n";

                        qDebug() << "t_pose_assigned_number: " <<t_pose_assigned_number << "\n";
                        qDebug() << "t_pose_repeated_number: " <<t_pose_repeated_number << "\n";

                        qDebug() << "squat_assigned_number: " <<squat_assigned_number << "\n";
                        qDebug() << "squat_repeated_number: " <<squat_repeated_number << "\n";

                        qDebug() << "right_knee_assigned_number: " <<right_knee_assigned_number << "\n";
                        qDebug() << "right_knee_repeated_number: " <<right_knee_repeated_number << "\n";

                        qDebug() << "left_knee_assigned_number: " <<left_knee_assigned_number << "\n";
                        qDebug() << "left_knee_repeated_number: " <<left_knee_repeated_number << "\n";

                        qDebug() << "zombie_assigned_number: " <<zombie_assigned_number << "\n";
                        qDebug() << "zombie_repeated_number: " <<zombie_repeated_number << "\n";
                        break;

                    }
                    qDebug() << "Received: " << buffer <<  "\n";

                // status   =    "not_valid" hareket geçerli değil
                //          =    "new_move"   yeri hareket yapıldı
                //         =     "move_next"  yeni harekete geç
                //         =     "continue"   hareket devam ediyor
                //         =     "done"       hareket bitti
                //         =      "started"    hareket başladı


                    int result = sscanf(buffer, "%s %f %s %d", move_name, &probability, status, &repetition);

                    if(strcmp(status, "not_valid") == 0){
                        qDebug() << move_name << ":Hareket geçerli değil.\n";
                    }

                    if(strcmp(status, "new_move") == 0){
                        qDebug() << move_name << ":Yeni hareket algılandı.\n";
                    }

                    if(strcmp(status, "continue") == 0){
                        qDebug() << move_name << ":Harekete devam ediliyor...\n";
                    }


                    if(strcmp(status, "started") == 0){
                        qDebug() << move_name << ":Hareket başlatıldı\n";
                    }

                    //strcmp(status, "move_next") == 0) ||
                    if(( strcmp(status, "done") == 0)){

                                if(strcmp(status, "done") == 0){
                                    qDebug() << move_name << ":hareket bitti\n";
                                }

                                if(strcmp(status, "move_next") == 0){
                                    qDebug() << move_name << ":yeni harekete geç\n";
                                }

                                    if(strcmp(move_name, "right_head") == 0){

                                        if(right_head_assigned_number == 0){

                                        }
                                        else{
                                            right_head_repeated_number += 1;
                                            emit updateRightHeadProgress((int)(((float)right_head_repeated_number / (float)right_head_assigned_number) * 100), right_head_repeated_number);
                                        }

                                    }
                                    if(strcmp(move_name, "left_head") == 0){

                                        if(left_head_assigned_number == 0){

                                        }
                                        else{
                                            left_head_repeated_number +=1;
                                            emit updateLeftHeadProgress((int)(((float)left_head_repeated_number / (float)left_head_assigned_number) * 100), left_head_repeated_number);
                                        }

                                    }
                                    if(strcmp(move_name, "left_arm") == 0){

                                        if(left_arm_assigned_number == 0){

                                        }
                                        else{
                                            left_arm_repeated_number +=1;
                                            emit updateLeftArmProgress((int)(((float)left_arm_repeated_number / (float)left_arm_assigned_number) * 100), left_arm_repeated_number);
                                        }

                                    }
                                    if(strcmp(move_name, "right_arm") == 0){

                                        if(right_arm_assigned_number == 0){

                                        }
                                        else{
                                            right_arm_repeated_number +=1;
                                            emit updateRightArmProgress((int)(((float)right_arm_repeated_number / (float)right_arm_assigned_number) * 100), right_arm_repeated_number);
                                        }
                                    }
                                    if(strcmp(move_name, "t_pose") == 0){

                                        if(t_pose_assigned_number == 0){

                                        }
                                        else{
                                            t_pose_repeated_number +=1;
                                            emit updateTposeProgress((int)(((float)t_pose_repeated_number / (float)t_pose_assigned_number) * 100), t_pose_repeated_number);
                                        }
                                    }
                                    if(strcmp(move_name, "squat") == 0){
                                        if(squat_assigned_number == 0 ){

                                        }
                                        else{
                                            squat_repeated_number +=1;
                                            emit updateSquatProgress((int)(((float)squat_repeated_number / (float)squat_assigned_number) * 100), squat_repeated_number);
                                        }
                                    }
                                    if(strcmp(move_name, "right_knee") == 0){
                                        if(right_knee_assigned_number ==0 ){

                                        }
                                        else{

                                            right_knee_repeated_number += 1;
                                            emit updateRightKneeProgress((int)(((float)right_knee_repeated_number / (float)right_knee_assigned_number) * 100), right_knee_repeated_number);
                                        }

                                    }
                                    if(strcmp(move_name, "left_knee") == 0){
                                        if(left_knee_assigned_number == 0 ){

                                        }
                                        else{
                                            left_knee_repeated_number +=1;
                                            emit updateLeftKneeProgress((int)(((float)left_knee_repeated_number / (float)left_knee_assigned_number) * 100), left_knee_repeated_number);
                                        }
                                    }
                                    if(strcmp(move_name, "zombie") == 0){

                                        if(zombie_assigned_number == 0){

                                        }
                                        else{
                                            zombie_repeated_number +=1 ;
                                            emit updateZombieProgress((int)(((float)zombie_repeated_number / (float)zombie_assigned_number) * 100), zombie_repeated_number);
                                        }
                                    }
                    }

                }
            }
        }


}

}

/*void Worker::requestStop() {
    shouldStop = true;
    qDebug() << "REQUESTING STOP\n";
}*/
