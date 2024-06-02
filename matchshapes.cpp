#include "matchshapes.h"
#include "ui_matchshapes.h"
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <iostream>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/document/value.hpp>
#include <memory>  // Include for std::unique_ptr
#include <userinfo.h>
#include <QMessageBox>
#include <bsoncxx/types.hpp>
#include <mainwindow.h>

matchshapes::matchshapes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matchshapes)
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

    connect(backButton_s, &QPushButton::clicked, this, &matchshapes::handleBackButton_s); // Corrected connect statement

    // Ensure the button is always on top and doesn't move
    backButton_s->setFlat(true);
    backButton_s->raise(); // Bring the button to the front
    backButton_s->show();

}
void matchshapes::handleBackButton_s(){
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

matchshapes::~matchshapes()
{
    delete ui;
}

void matchshapes::on_pushButton_clicked()
{
    QString circle_info = ui->label_circle->text();
    QString triangle_info = ui->label_triangle->text();
    QString pentagon_info = ui->label_pentagon->text();
    QString rectangle_info = ui->label_rectangle->text();
    QString line_info = ui->label_line->text();

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
            sub_doc.append(bsoncxx::builder::basic::kvp("shape_circle", circle_info.toStdString()),
                           bsoncxx::builder::basic::kvp("shape_triangle", triangle_info.toStdString()),
                           bsoncxx::builder::basic::kvp("shape_pentagon", pentagon_info.toStdString()),
                           bsoncxx::builder::basic::kvp("shape_rectangle", rectangle_info.toStdString()),
                           bsoncxx::builder::basic::kvp("shape_line", line_info.toStdString()),
                           bsoncxx::builder::basic::kvp("are_shapes_matched", true)); // Ensure this is part of the $set operation
        }));

        // Perform the update operation
        collection.update_one(filter_builder.view(), update_builder.view());
        QMessageBox::information(this, "Şekil Eşleştirme", "Şekil Eşleştirme başarıyla tamamlandı, ana menüye dönebilirsiniz.");
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
    }
}


