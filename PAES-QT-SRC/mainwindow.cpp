#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QProcess>
#include <canvas.h>
#include <matchshapes.h>
#include <exercises.h>
#include <userinfo.h>
#include <memory>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <iostream>

#include <QMessageBox>
#include <QtNetwork>
#include <QCoreApplication>
#include <chrono>
#include <sstream>
#include <iomanip>

std::string getFormattedDateTime2() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , process(nullptr)

{
    ui->setupUi(this);

    auto patient_data = UserInfo::getInstance()->getPatientData();
    bsoncxx::document::view view = patient_data.view();
    auto name = std::string(view["name"].get_string().value);
    auto surname = std::string(view["surname"].get_string().value);
    auto gender = std::string(view["gender"].get_string().value);

    std::string formatted_text = name + " " + surname + " - Gender: " + gender;

    // Set the formatted text to the UI element
    ui->name_surname->setText(QString::fromStdString(formatted_text));}

MainWindow::~MainWindow()
{
    terminatePythonServer();
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    terminatePythonServer();
    event->accept();
}

//Oyunlar menüsü butonu
void MainWindow::on_pushButton_3_clicked()
{
    terminatePythonServer();
    if (ui->pushButton_3) {
        ui->pushButton_3->setEnabled(false);
    }
    game = new Games();
    game->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    game->showMaximized();

    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();
    if (ui->pushButton_3) {
        ui->pushButton_3->setEnabled(true);
    }
}

//Hasta bakıcı çağır butonu
void MainWindow::on_pushButton_clicked()
{
    terminatePythonServer();
    bool are_shapes_matched = false; // Default value

    try {
        const bsoncxx::document::value& patientData = UserInfo::getInstance()->getPatientData();
        auto view = patientData.view();  // Now declaring 'view' correctly

        bsoncxx::document::element element = view["are_shapes_matched"];
        if (element && element.type() == bsoncxx::type::k_bool) {
            are_shapes_matched = element.get_bool().value;
        }

    } catch (const std::exception& e) {
        // Handle the case where patientData might not be initialized or other errors
        std::cerr << "Error accessing patient data: " << e.what() << std::endl;
    }

    if (are_shapes_matched) {
        if (ui->pushButton) {
            ui->pushButton->setEnabled(false);
        }
        Canvas *c = new Canvas();
        c->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        c->showFullScreen();

        // Process pending events to ensure the new window is rendered
        QApplication::processEvents();

        // Then hide the current window
        this->hide();
        if (ui->pushButton) {
            ui->pushButton->setEnabled(true);
        }

    } else {
        if (ui->pushButton) {
            ui->pushButton->setEnabled(false);
        }
        matchshapes *ms = new matchshapes();
        ms->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        ms->showFullScreen();
        // Process pending events to ensure the new window is rendered
        QApplication::processEvents();

        // Then hide the current window
        this->hide();
        if (ui->pushButton) {
            ui->pushButton->setEnabled(true);
        }

    }
}

//Egzersizler butonu
void MainWindow::on_pushButton_2_clicked()
{
    terminatePythonServer();

    try {
        auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
        auto collection = client["paes"]["patients"];

        auto patient_data = UserInfo::getInstance()->getPatientData();
        bsoncxx::document::view pData = patient_data.view();
        auto patient_id = pData["_id"].get_oid();

        auto result = collection.find_one(patient_data.view());

        if (result) {
            auto patient_data_2 = std::make_unique<bsoncxx::document::value>(*result);
            UserInfo::getInstance()->setPatientData(std::move(patient_data_2));

            //QMessageBox::information(nullptr, "Data Refresh", "Patient data refreshed successfully.");
        } else {
            QMessageBox::warning(nullptr, "Data Refresh", "No patient found with the given ID.");
        }
    } catch (const mongocxx::exception& e) {
        QMessageBox::critical(nullptr, "Database Error", QString::fromStdString(e.what()));
    }
    if (ui->pushButton_2) {
        ui->pushButton_2->setEnabled(false);
    }
    exercises *e = new exercises();
    e->setWindowFlags(Qt::Window | Qt::FramelessWindowHint );
    e->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();
    if (ui->pushButton_2) {
        ui->pushButton_2->setEnabled(true);
    }
}


//establish video connection
void MainWindow::on_pushButton_4_clicked()
{
    if(!process){

        QString ScriptPath = QCoreApplication::applicationDirPath() + "/server.py";
        QString ip = "DEBUG"; // Default IP address in case no network IP is found

        // Retrieve local IP address
        QList<QHostAddress> list = QNetworkInterface::allAddresses();
        for (int nIter=0; nIter<list.count(); nIter++)
        {
            if (!list[nIter].isLoopback() && list[nIter].protocol() == QAbstractSocket::IPv4Protocol)
            {
                ip = list[nIter].toString();
                break;
            }
        }
        QString fullAddress = ip + ":4545";  // Concatenate the port number to the IP address
        qDebug() << "Using IP Address:" << fullAddress;

        try {
            auto patient_data = UserInfo::getInstance()->getPatientData();
            bsoncxx::document::view pData = patient_data.view();
            auto patient_id = pData["_id"].get_oid();
            // Setup MongoDB client
            auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
            auto collection = client["paes"]["patients"];

            // Filter document to locate the existing caregiver using patient_id (adjust as necessary)
            bsoncxx::builder::basic::document filter_builder{};
            filter_builder.append(bsoncxx::builder::basic::kvp("_id", patient_id));  // Use ObjectId here

            // Prepare the update operation
            bsoncxx::builder::basic::document update_builder{};
            update_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document sub_doc) {
                sub_doc.append(bsoncxx::builder::basic::kvp("connection_address", fullAddress.toStdString())),
                sub_doc.append(bsoncxx::builder::basic::kvp("requested_connection_time", getFormattedDateTime2())),
                sub_doc.append(bsoncxx::builder::basic::kvp("requested_video_connection", true));
            }));

            // Execute the update
            collection.update_one(filter_builder.view(), update_builder.view());

            qDebug() << "Database updated with new IP address";

        } catch (const mongocxx::exception& e) {
            std::cerr << "Error accessing or updating MongoDB data: " << e.what() << std::endl;
        }

        startPythonServer(ip);
    }
    else{
        terminatePythonServer();
    }

}


void MainWindow::startPythonServer(const QString &ip)
{
    if (process) {
        qDebug() << "startPythonServer: Terminating existing process...";
        terminatePythonServer();
        QMessageBox::warning(this,"Görüntü Aktarma", "Görüntü Aktarımı tespit edildi, eski bağlantı kapatılıyor.");
        ui->pushButton_4->setStyleSheet("QPushButton { background:rgb(153, 193, 241); }");

    }
    else{
        qDebug() << "startPythonServer: Starting new process...";
        process = new QProcess(this);
        QString scriptPath = QCoreApplication::applicationDirPath() + "/server.py";
        QString command = "python3";
        QStringList args = {scriptPath, ip};

        connect(process, &QProcess::finished, this, &MainWindow::onProcessFinished);
        connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::handleStandardOutput);
        connect(process, &QProcess::readyReadStandardError, this, &MainWindow::handleStandardError);

        process->start(command, args);

        if (!process->waitForStarted()) {
            qDebug() << "startPythonServer: Failed to start the server.";
        } else {
            qDebug() << "startPythonServer: Server started successfully with IP:" << ip;
            ui->pushButton_4->setStyleSheet("QPushButton { background-color: green; }");
            QMessageBox::information(this, "Görüntü Sağlama", "Görüntü hastabakıcının erişimine açıldı.");
        }
    }

}

void MainWindow::terminatePythonServer()
{
    if (process) {
        qDebug() << "terminatePythonServer: Terminating process...";
        process->terminate();
        if (!process->waitForFinished(3000)) { // Wait up to 3 seconds
            process->kill(); // Force kill if it doesn't terminate
        }
        delete process;
        process = nullptr;
    }
}

void MainWindow::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit) {
        qDebug() << "onProcessFinished: The process crashed.";
        ui->pushButton_4->setStyleSheet("QPushButton { background-color: red; }");
        QMessageBox::critical(this, "Görüntü Kesildi", "Beklenmedik bir hata.");
    } else {
        qDebug() << "onProcessFinished: The process finished successfully with exit code:" << exitCode;
        ui->pushButton_4->setStyleSheet("QPushButton { background:rgb(153, 193, 241); }");
        QMessageBox::information(this, "Görüntü Kesildi", "Görüntü kontrollü bir şekilde kapatıldı.");
    }

    qDebug() << "onProcessFinished: Cleaning up process...";
    terminatePythonServer();
}

// Handle standard output from the Python server
void MainWindow::handleStandardOutput()
{
    QProcess *proc = qobject_cast<QProcess *>(sender());
    if (proc) {
        QString output = proc->readAllStandardOutput();
        qDebug() << "handleStandardOutput: Python Output:" << output;
    }
}

// Handle standard error from the Python server
void MainWindow::handleStandardError()
{
    QProcess *proc = qobject_cast<QProcess *>(sender());
    if (proc) {
        QString errorOutput = proc->readAllStandardError();
        qDebug() << "handleStandardError: Python Error:" << errorOutput;
    }
}
