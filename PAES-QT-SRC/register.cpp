#include "register.h"
#include "ui_register.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include "login.h"
Register::Register(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    backButton = new QPushButton(tr("<-"), this);
    backButton->setStyleSheet(
        "QPushButton {"
        "   color: black;"              // Ensure text color is black
        "   background-color: white;"   // Button background is white
        "   border-style: none;"        // No border for a flat look
        "   border: 1px solid #8f8f91;"
        "   border-radius: 10px;"
        "   padding: 5px 10px;"         // Adjust padding to match the visual weight
        "   font-size: 16px;"           // Ensure font size is sufficiently large
        "}"
        );
    connect(backButton, &QPushButton::clicked, this, &Register::handleBackButton);
    backButton->setFixedSize(40, 40);  // Set a fixed size for the button
    backButton->setGeometry(5, 25, backButton->width(), backButton->height());  // X, Y, Width, Height
    backButton->setCursor(Qt::PointingHandCursor);

}
void Register::handleBackButton() {
    //For example, just close this window
    if (backButton) {
        backButton->setEnabled(false);
    }
    Login * log = new Login();
    log->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    log->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();
    if (backButton) {
        backButton->setEnabled(true);
    }

}
Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{

    QString room_number = ui->input_room_number->text();
    QString patient_number = ui->input_patient_number->text();
    QString name = ui->input_name->text();
    QString surname = ui->input_surname->text();
    QString gender;

    if (ui->radioButton->isChecked()) {
        gender = "male";
    }
    else if(ui->radioButton_2->isChecked()) {
        gender = "female";
    }

    DBManager& dbManager = DBManager::getInstance();

    auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
    auto collection = client["paes"]["patients"];
    // Use the instance to call findPatient
    auto maybe_result = dbManager.findPatient(room_number, patient_number);

    if(maybe_result){
        QMessageBox::warning(this, "Register Error",
                             "Patient with the specified number, already exists cannot register a new patient.");
    }
    else {
        using bsoncxx::builder::basic::kvp;
        using bsoncxx::builder::basic::make_document;

        auto document = make_document(
            kvp("room_number", room_number.toStdString()),
            kvp("patient_number", patient_number.toStdString()),
            kvp("shape_rectangle", ""),
            kvp("shape_circle", ""),
            kvp("shape_pentagon", ""),
            kvp("shape_triangle", ""),
            kvp("shape_line", ""),
            kvp("are_shapes_matched", false),
            kvp("personal_caregiver", ""),
            kvp("connection_address", ""),
            kvp("requested_video_connection", false),
            kvp("requested_connection_time", ""),
            kvp("gender", gender.toStdString()),
            kvp("name", name.toStdString()),
            kvp("surname", surname.toStdString()),
            kvp("todays_exercises", make_document(
                                        kvp("right_head", make_document(
                                                              kvp("assigned_number", 0),
                                                              kvp("repeated_number", 0)
                                                              )),
                                        kvp("left_head", make_document(
                                                             kvp("assigned_number", 0),
                                                             kvp("repeated_number", 0)
                                                             )),
                                        kvp("right_arm", make_document(
                                                            kvp("assigned_number", 0),
                                                            kvp("repeated_number", 0)
                                                            )),
                                        kvp("left_arm", make_document(
                                                           kvp("assigned_number", 0),
                                                           kvp("repeated_number", 0)
                                                           )),
                                        kvp("t_pose", make_document(
                                                          kvp("assigned_number", 0),
                                                          kvp("repeated_number", 0)
                                                            )),
                                        kvp("squat", make_document(
                                                            kvp("assigned_number", 0),
                                                            kvp("repeated_number", 0)
                                                            )),
                                        kvp("right_knee", make_document(
                                                           kvp("assigned_number", 0),
                                                          kvp("repeated_number", 0)
                                                           )),
                                        kvp("left_knee", make_document(
                                                           kvp("assigned_number", 0),
                                                           kvp("repeated_number", 0)
                                                           )),
                                        kvp("zombie", make_document(
                                                           kvp("assigned_number", 0),
                                                           kvp("repeated_number", 0)
                                                           ))
                                                  )),
            kvp("are_exercises_assigned", false),
            kvp("are_exercises_completed", false)
            );

        collection.insert_one(document.view());
        QMessageBox::information(this, "Patient Register",
                            "Hasta Başarıyla Sisteme Kaydedildi.");
    }

}

