#include "exercises.h"
#include "ui_exercises.h"
#include <QMessageBox>
#include <userinfo.h>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/document/value.hpp>
#include <QProcess>
#include <QFile>
#include <QThread>
#include <pthread.h>
#include <worker.h>
#include <QPushButton>
#include <mainwindow.h>

Worker* worker = nullptr;
QPushButton *backButton_s;
using namespace std;
exercises::exercises(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::exercises)
{
    ui->setupUi(this);

    backButton_s = new QPushButton("<-", this);
    backButton_s->setStyleSheet(
        "QPushButton {"
        "   color: black;"              // Ensure text color is black
        "   background-color: white;"   // Button background is white
        "   border-style: none;"        // No border for a flat look
        "   border: 1px solid #8f8f91;"
        "   border-radius: 7px;"
        "   padding: 5px 10px;"         // Adjust padding to match the visual weight
        "   font-size: 16px;"           // Ensure font size is sufficiently large
        "}"
        );

    // Set cursor to pointing hand when hovering over the button
    backButton_s->setCursor(Qt::PointingHandCursor);

    // Position the button to match the provided image layout
    backButton_s->setGeometry(10, 10, 35, 35);  // Adjust size to match the image

    connect(backButton_s, &QPushButton::clicked, this, &exercises::handleBackButton_s); // Corrected connect statement

    // Ensure the button is always on top and doesn't move
    backButton_s->setFlat(true);
    backButton_s->raise(); // Bring the button to the front
    backButton_s->show();
    connect(this, &exercises::operatePythonProcess, this, &exercises::startPythonProcess);
    connect(this, &exercises::operateCppProcess, this, &exercises::startCppProcess);
    connect(this, &exercises::terminateProcesses, this, &exercises::stopProcesses);
    connect(this, &exercises::serverOperation, this, &exercises::startServerThread);
    //connect(this, &exercises::terminateThread, this, &exercises::terminateServerThread);
    connect(this, &exercises::stopWork, worker, &Worker::stopWork);
    connect(worker, &QThread::finished, worker, &QObject::deleteLater);


    bool connected = connect(this, &exercises::terminateThread, this, &exercises::terminateServerThread);
    qDebug() << "Connection status: " << connected;


    ui->kafa_sag_bar->setMinimum(0);
    ui->kafa_sag_bar->setMaximum(100);

    ui->kafa_sol_bar->setMinimum(0);
    ui->kafa_sol_bar->setMaximum(100);

    ui->zombie_bar->setMinimum(0);
    ui->zombie_bar->setMaximum(100);

    ui->squat_bar->setMinimum(0);
    ui->squat_bar->setMaximum(100);

    ui->sag_diz_bar->setMinimum(0);
    ui->sag_diz_bar->setMaximum(100);

    ui->sol_diz_bar->setMinimum(0);
    ui->sol_diz_bar->setMaximum(100);

    ui->sag_kol_bar->setMinimum(0);
    ui->sag_kol_bar->setMaximum(100);

    ui->sol_kol_bar->setMinimum(0);
    ui->sol_kol_bar->setMaximum(100);

    ui->t_poz_bar->setMinimum(0);
    ui->t_poz_bar->setMaximum(100);

    auto patient_data = UserInfo::getInstance()->getPatientData();
    bsoncxx::document::view pData = patient_data.view();
    auto todays_exercises = pData["todays_exercises"].get_document().value;




    auto t_pose = todays_exercises["t_pose"].get_document().value;
    if( t_pose["assigned_number"].get_int32().value==0){
        ui->t_poz_bar->setValue(100);
    }
    else{

        if(t_pose["repeated_number"].get_int32().value != 0){

            if(t_pose["repeated_number"].get_int32().value > t_pose["assigned_number"].get_int32().value){
                ui->t_poz_bar->setValue(100);
            }

            else{
                ui->t_poz_bar->setValue( ((int)(((float)t_pose["repeated_number"].get_int32().value / (float)t_pose["assigned_number"].get_int32().value) * 100)));
            }
        }
        else{
            ui->t_poz_bar->setValue(0);
        }
    }

    auto right_arm = todays_exercises["right_arm"].get_document().value;
    if(right_arm["assigned_number"].get_int32().value==0){
        ui->sag_kol_bar->setValue(100);
    }
    else{

        if(right_arm["repeated_number"].get_int32().value != 0){

        if(right_arm["repeated_number"].get_int32().value > right_arm["assigned_number"].get_int32().value){
                ui->sag_kol_bar->setValue(100);
            }
        else
            ui->sag_kol_bar->setValue( ((int)(((float)right_arm["repeated_number"].get_int32().value / (float)right_arm["assigned_number"].get_int32().value) * 100)));

        }
        else{
            ui->sag_kol_bar->setValue(0);
        }

    }
    auto left_arm = todays_exercises["left_arm"].get_document().value;
    if( left_arm["assigned_number"].get_int32().value==0){
         ui->sol_kol_bar->setValue(100);
    }
    else{

        if(left_arm["repeated_number"].get_int32().value != 0){



            if(left_arm["repeated_number"].get_int32().value > left_arm["assigned_number"].get_int32().value){
                ui->sol_kol_bar->setValue(100);
            }

            else
                ui->sol_kol_bar->setValue( ((int)(((float)left_arm["repeated_number"].get_int32().value / (float)left_arm["assigned_number"].get_int32().value) * 100)));
        }


        else{
            ui->sol_kol_bar->setValue(0);
        }

    }
    auto right_head = todays_exercises["right_head"].get_document().value;
    if(right_head["assigned_number"].get_int32().value==0){
        ui->kafa_sag_bar->setValue(100);

    }
    else{
        if(right_head["repeated_number"].get_int32().value != 0){

            if(right_head["repeated_number"].get_int32().value > right_head["assigned_number"].get_int32().value){
                ui->kafa_sag_bar->setValue(100);
            }
            else
                ui->kafa_sag_bar->setValue( ((int)(((float)right_head["repeated_number"].get_int32().value / (float)right_head["assigned_number"].get_int32().value) * 100)));
        }
        else{
            ui->kafa_sag_bar->setValue(0);
        }
    }

    auto left_head = todays_exercises["left_head"].get_document().value;
    if(left_head["assigned_number"].get_int32().value==0){
        ui->kafa_sol_bar->setValue(100);

    }
    else{
        if(left_head["repeated_number"].get_int32().value != 0){

            if(left_head["repeated_number"].get_int32().value > left_head["assigned_number"].get_int32().value){
                ui->kafa_sol_bar->setValue(100);
            }
            else
                ui->kafa_sol_bar->setValue( ((int)(((float)left_head["repeated_number"].get_int32().value / (float)left_head["assigned_number"].get_int32().value) * 100)));
        }
        else{
            ui->kafa_sol_bar->setValue(0);
        }

    }
    auto squat = todays_exercises["squat"].get_document().value;
    if(  squat["assigned_number"].get_int32().value==0){
        ui->squat_bar->setValue(100);

    }
    else{
        if(squat["repeated_number"].get_int32().value != 0){
            if(squat["repeated_number"].get_int32().value > squat["assigned_number"].get_int32().value){
                ui->squat_bar->setValue(100);
            }
            else
                ui->squat_bar->setValue( ((int)(((float)squat["repeated_number"].get_int32().value / (float)squat["assigned_number"].get_int32().value) * 100)));
        }
        else{
            ui->squat_bar->setValue(0);
        }
    }

    auto zombie = todays_exercises["zombie"].get_document().value;
    if(zombie["assigned_number"].get_int32().value==0){
        ui->zombie_bar->setValue(100);

    }
    else{
        if(zombie["repeated_number"].get_int32().value != 0){
            if(zombie["repeated_number"].get_int32().value > zombie["assigned_number"].get_int32().value){
                ui->zombie_bar->setValue(100);
            }
            else
                ui->zombie_bar->setValue( ((int)(((float)zombie["repeated_number"].get_int32().value / (float)zombie["assigned_number"].get_int32().value) * 100)));

        }
        else{
            ui->zombie_bar->setValue(0);
        }

    }
    auto right_knee = todays_exercises["right_knee"].get_document().value;
    if(right_knee["assigned_number"].get_int32().value==0){
        ui->sag_diz_bar->setValue(100);

    }
    else{
        if(right_knee["repeated_number"].get_int32().value != 0){
            if(right_knee["repeated_number"].get_int32().value > right_knee["assigned_number"].get_int32().value){
                ui->sag_diz_bar->setValue(100);
            }
            else
                ui->sag_diz_bar->setValue( ((int)(((float)right_knee["repeated_number"].get_int32().value / (float)right_knee["assigned_number"].get_int32().value) * 100)));
        }
        else{
            ui->sag_diz_bar->setValue(0);
        }
    }

    auto left_knee = todays_exercises["left_knee"].get_document().value;
    if(left_knee["assigned_number"].get_int32().value==0){
        ui->sol_diz_bar->setValue(100);

    }
    else{
        if(left_knee["repeated_number"].get_int32().value != 0){
            if(left_knee["repeated_number"].get_int32().value > left_knee["assigned_number"].get_int32().value){
                ui->sol_diz_bar->setValue(100);
            }
            else
            ui->sol_diz_bar->setValue( ((int)(((float)left_knee["repeated_number"].get_int32().value / (float)left_knee["assigned_number"].get_int32().value) * 100)));
        }
        else{
            ui->sol_diz_bar->setValue(0);
        }
    }

}
void exercises::handleBackButton_s(){
    emit terminateProcesses();
    //sleep(3);
    emit terminateThread();
    if (backButton_s) {
        backButton_s->setEnabled(false);
    }


    MainWindow *main3 = new MainWindow();
    main3->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    main3->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();

    if (backButton_s) {
        backButton_s->setEnabled(true);
    }
}

exercises::~exercises()
{
    delete ui;
}

int serverSocket = -1;
int clientSocket = -1;


void handle_sigint(int sig) {
    std::cout << "\nCaught signal " << sig << " . Exiting gracefully...\n";

    //send to pose_cpp signal for terminate

    close(clientSocket); // Close the client socket
    close(serverSocket); // Close the server socket


    exit(0); // Exit the program
}

void exercises::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit) {
        qDebug() << "onProcessFinished: The process crashed.";
    } else {
        qDebug() << "onProcessFinished: The process finished successfully with exit code:" << exitCode;
    }

    qDebug() << "onProcessFinished: Cleaning up process...";
}

void exercises::handleStandardOutput()
{
    QProcess *proc = qobject_cast<QProcess *>(sender());
    if (proc) {
        QString output = proc->readAllStandardOutput();
        qDebug() << "handleStandardOutput: Process Output:" << output;
    }
}

void exercises::handleStandardError()
{
    QProcess *proc = qobject_cast<QProcess *>(sender());
    if (proc) {
        QString errorOutput = proc->readAllStandardError();
        qDebug() << "handleStandardError: Process Error:" << errorOutput;
    }
}
void exercises::closeEvent(QCloseEvent *event) {
    emit terminateProcesses();
    //exit_while = true;
    event->accept();
}
void exercises::startPythonProcess(const QString &command, const QStringList &arguments) {
    qDebug()<<"in pythons strat process\n";

    if (!process_py) {
        process_py = new QProcess(this);
        connect(process_py, &QProcess::finished, this, &exercises::onProcessFinished);
        //connect(process_py, &QProcess::readyReadStandardOutput, this, &exercises::handleStandardOutput);
        //connect(process_py, &QProcess::readyReadStandardError, this, &exercises::handleStandardError);
    }
    process_py->start(command, arguments);
    if (!process_py->waitForStarted()) {
        qDebug() << "Failed to start python process:" << process_py->errorString();

    }
}

void exercises::startCppProcess(const QString &path) {
    qDebug()<<"in pythons cpp process\n";

    if (!process_cpp) {
        process_cpp = new QProcess(this);
        connect(process_cpp, &QProcess::finished, this, &exercises::onProcessFinished);
        //connect(process_cpp, &QProcess::readyReadStandardError, this, &exercises::handleStandardError);
    }
    process_cpp->start(path);
    if (!process_cpp->waitForStarted()) {
        qDebug() << "Failed to start cpp process:" << process_cpp->errorString();
    }
}

void exercises::stopProcesses() {

    if (process_py) {
        process_py->terminate();
        process_py->waitForFinished(500);
        delete process_py;
        process_py = nullptr;
    }

    if (process_cpp) {
        process_cpp->terminate();
        process_cpp->waitForFinished(500);
        delete process_cpp;
        process_cpp = nullptr;
    }


}

void exercises::startServerThread() {
    worker = new Worker();
    worker->start();

    qDebug() << "before connect";
    connect(worker, &Worker::updateRightHeadProgress, this, &exercises::updateRightHeadProgressBar);
    connect(worker, &Worker::updateLeftHeadProgress, this, &exercises::updateLeftHeadProgressBar);
    connect(worker, &Worker::updateLeftArmProgress, this, &exercises::updateLeftArmProgressBar);
    connect(worker, &Worker::updateRightArmProgress, this, &exercises::updateRightArmProgressBar);

    connect(worker, &Worker::updateTposeProgress, this, &exercises::updateTposeProgressBar);
    connect(worker, &Worker::updateSquatProgress, this, &exercises::updateSquatProgressBar);
    connect(worker, &Worker::updateRightKneeProgress, this, &exercises::updateRightKneeProgressBar);
    connect(worker, &Worker::updateLeftKneeProgress, this, &exercises::updateLeftKneeProgressBar);
    connect(worker, &Worker::updateZombieProgress, this, &exercises::updateZombieProgressBar);

    qDebug() << "after connect";
}


void exercises::on_neck_right_clicked()
{    if (process_cpp) {
        process_cpp->terminate();
        process_cpp->waitForFinished(500);
        delete process_cpp;
        process_cpp = nullptr;
    }
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigint);

    qDebug()<<"on click\n";
    emit operateCppProcess(QCoreApplication::applicationDirPath() + "/onnx_pose/build/pose_generator");
    qDebug()<<"after operate cpp process\n";

    emit operatePythonProcess("python3", {QCoreApplication::applicationDirPath() + "/rf/rf_onxx.py"});
    qDebug()<<"after operate pytjhon process\n";

    emit serverOperation(1235);
}

void exercises::terminateServerThread() {
    if(worker){

        if (worker->isFinished()){
            qDebug() << "NOT THREAD OR WORKER\n";

            return; // Guard against null pointers if the thread or worker isn't set up
        }
        qDebug() << "INVOKED TERMINATESERVERTHREAD\n";
        // Request the worker to stop
        //worker->shouldStop = true;
        //qDebug() << "SHOULDSTOP: "<< worker->shouldStop;

        //emit stopWork();
        qDebug() << "INVOKED SHOLUDSSSTOP CHANGED\n";
        if (worker->isRunning()) { // Wait for 3 seconds,
            qDebug() << "dsşdlfks";
            qWarning("Thread did not finish in time, forcing termination");
            worker->quit(); // Force terminate the thread (use with caution)
            //worker->wait(); // Ensure it has really finished
        }

    }


}

void exercises::on_pushButton_clicked()
{
    qDebug()<<"exit detected\n";

    if (ui->kafa_sag_bar->value() >= 100 &&
        ui->kafa_sol_bar->value() >= 100 &&
        ui->zombie_bar->value() >= 100 &&
        ui->squat_bar->value() >= 100 &&
        ui->sag_diz_bar->value() >= 100 &&
        ui->sol_diz_bar->value() >= 100 &&
        ui->sag_kol_bar->value() >= 100 &&
        ui->sol_kol_bar->value() >= 100 &&
        ui->t_poz_bar->value() >= 100){

        try {
            // Ensure there is existing patient data
            auto patient_data = UserInfo::getInstance()->getPatientData();
            bsoncxx::document::view view = patient_data.view();
            auto patient_id = view["_id"].get_oid().value;

            // MongoDB connection using URI with proper credentials
            auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
            auto collection = client["paes"]["patients"];
            // Filter document to locate the existing patient
            bsoncxx::builder::basic::document filter_builder{};
            filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

            // Update document with new shape info
            bsoncxx::builder::basic::document update_builder{};
            update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc) {
                sub_doc.append(bsoncxx::builder::basic::kvp("are_exercises_completed", true));
            }));


            // Perform the update operation
            collection.update_one(filter_builder.view(), update_builder.view());
        }
        catch (const mongocxx::exception& e) {
            std::cerr << "MongoDB Error: " << e.what() << std::endl;
            QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
        }


    }

    emit terminateProcesses();
    sleep(3);
    emit terminateThread();
}

void exercises::updateRightHeadProgressBar(int value,int rep) {

    qDebug() << "REP: "<< rep << "\n";


    QMetaObject::invokeMethod(this, [this, value]() {
            ui->kafa_sag_bar->setValue(value);
            ui->kafa_sag_bar->update(); // veya ui->kafa_sag_bar->repaint();
        }, Qt::QueuedConnection);


    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc) {
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.right_head.repeated_number", rep));
        }));



        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        qDebug()<<"Dataabase error";

        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }


}

void exercises::updateLeftHeadProgressBar(int value,int rep) {

    QMetaObject::invokeMethod(this, [this, value]() {
        ui->kafa_sol_bar->setValue((int)value);
        ui->kafa_sol_bar->update(); // veya ui->kafa_sag_bar->repaint();

    }, Qt::QueuedConnection);

    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc) {
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.left_head.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        qDebug()<<"Dataabase error";

        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }

}


void exercises::updateRightArmProgressBar(int value,int rep) {

    QMetaObject::invokeMethod(this, [this, value]() {
            ui->sag_kol_bar ->setValue(value);
            ui->sag_kol_bar->update(); // veya ui->kafa_sag_bar->repaint();
        }, Qt::QueuedConnection);

    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc){
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.right_arm.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        qDebug()<<"Dataabase error";
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}

void exercises::updateLeftArmProgressBar(int value,int rep) {

    QMetaObject::invokeMethod(this, [this, value]() {
            ui->sol_kol_bar->setValue((int)value);
            ui->sol_kol_bar->update(); // veya ui->kafa_sag_bar->repaint();

        }, Qt::QueuedConnection);
    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc){
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.left_arm.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}

void exercises::updateTposeProgressBar(int value,int rep){
    QMetaObject::invokeMethod(this, [this, value]() {
            ui->t_poz_bar->setValue((int)value);
            ui->t_poz_bar->update(); // veya ui->kafa_sag_bar->repaint();

        }, Qt::QueuedConnection);

    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc){
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.t_pose.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}


void exercises::updateSquatProgressBar(int value,int rep){
    QMetaObject::invokeMethod(this, [this, value]() {
            ui->squat_bar->setValue((int)value);
            ui->squat_bar->update(); // veya ui->kafa_sag_bar->repaint();

        }, Qt::QueuedConnection);
    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc){
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.squat.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        qDebug()<<"Dataabase  squat error";

        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}


void exercises::updateRightKneeProgressBar(int value,int rep){
    QMetaObject::invokeMethod(this, [this, value]() {
            ui->sag_diz_bar->setValue((int)value);
            ui->sag_diz_bar->update(); // veya ui->kafa_sag_bar->repaint();

        }, Qt::QueuedConnection);

    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc){
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.right_knee.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}


void exercises::updateLeftKneeProgressBar(int value,int rep){
    QMetaObject::invokeMethod(this, [this, value]() {
            ui->sol_diz_bar->setValue((int)value);
            ui->sol_diz_bar->update(); // veya ui->kafa_sag_bar->repaint();

        }, Qt::QueuedConnection);


    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc){
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.left_knee.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}
void exercises::updateZombieProgressBar(int value,int rep){
    QMetaObject::invokeMethod(this, [this, value]() {
            ui->zombie_bar->setValue((int)value);
            ui->zombie_bar->update(); // veya ui->kafa_sag_bar->repaint();

        }, Qt::QueuedConnection);

    try {
        // Ensure there is existing patient data
        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view view = patient_data.view();
        auto patient_id = view["_id"].get_oid().value;

        // MongoDB connection using URI with proper credentials
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];
        // Filter document to locate the existing patient
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));

        // Update document with new shape info
        bsoncxx::builder::basic::document update_builder{};
        update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc){
            sub_doc.append(bsoncxx::builder::basic::kvp("todays_exercises.zombie.repeated_number", rep));
        }));


        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const mongocxx::exception& e) {
        qDebug()<<"Dataabase error";

        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}
