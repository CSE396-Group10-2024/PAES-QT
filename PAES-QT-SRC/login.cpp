#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "userinfo.h"
#include "dbmanager.h"
#include "register.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QString executablePath = QCoreApplication::applicationDirPath();
    std::cout << "EXECPATH IS:::::::" << executablePath.toStdString() << std::endl;
}

Login::~Login()
{
    delete ui;
}
const bsoncxx::document::value& Login::getPatientData() const
{
    return *patientData; // Dereference the pointer to return the reference
}

void Login::on_pushButton_login_clicked()
{
    QString room_number = ui->lineEdit_room->text();
    QString patient_number = ui->lineEdit_patient->text();

    try {
        // Get the instance of DBManager
        DBManager& dbManager = DBManager::getInstance();

        // Use the instance to call findPatient
        auto maybe_result = dbManager.findPatient(room_number, patient_number);

        if (maybe_result) {
            // If a document is found, hide the login window and show the main window
            patientData = std::make_unique<bsoncxx::document::value>(*maybe_result);
            UserInfo::getInstance()->setPatientData(std::move(patientData));
            if (ui->pushButton_login) {
                ui->pushButton_login->setEnabled(false);
            }
            MainWindow *main = new MainWindow(this);
            main->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
            main->showFullScreen();
            // Process pending events to ensure the new window is rendered
            QApplication::processEvents();

            // Then hide the current window
            this->hide();
            if (ui->pushButton_login) {
                ui->pushButton_login->setEnabled(true);
            }
        } else {
            // If no document is found, show a warning message
            QMessageBox::warning(this, "Login Error",
                                 "Incorrect room or patient number. Please enter valid credentials.");
        }
    } catch (const mongocxx::exception& e) {
        // Handle MongoDB-specific exceptions
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error",
                              "Failed to connect to the database. Please check your connection settings.");
    } catch (const std::exception& e) {
        // Handle general exceptions
        std::cerr << "Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Error",
                              "An error occurred. Please try again.");
    }

}


void Login::on_pushButton_clicked()
{
    if (ui->pushButton) {
        ui->pushButton->setEnabled(false);
    }
    Register* R = new Register();
    R->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    R->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();
    // Then hide the current window
    this->hide();

    if (ui->pushButton) {
        ui->pushButton->setEnabled(true);
    }
}

