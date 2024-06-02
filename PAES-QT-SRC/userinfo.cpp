#include "userinfo.h"
#include "dbmanager.h"
#include <QMessageBox>

// Initialize the static member pointer
UserInfo* UserInfo::instance = nullptr;

UserInfo::UserInfo() {}

UserInfo* UserInfo::getInstance() {
    if (!instance) {
        instance = new UserInfo();
    }
    return instance;
}

void UserInfo::setPatientData(std::unique_ptr<bsoncxx::document::value> data) {
    patientData = std::move(data);
}

QString UserInfo::getColorForExercise(const QString& exerciseType) {
    auto patient_data = getPatientData();
    auto view = patient_data.view();
    // Navigate to the exercise document
    auto exerciseDoc = view[exerciseType.toStdString()];
    if (exerciseDoc && exerciseDoc.type() == bsoncxx::type::k_document) {
        // Access the document view
        auto exerciseView = exerciseDoc.get_document().view();
        // Check if 'is_assigned' exists and is a boolean
        auto element = exerciseView["is_assigned"];
        if (element && element.type() == bsoncxx::type::k_bool) {
            bool isAssigned = element.get_bool().value;
            if (isAssigned) {
                return "#B2EBF2";  // Example color if assigned
            }
        }
    }
    return "#E0F7FA";  // Default color if not assigned or not present
}


const bsoncxx::document::value& UserInfo::getPatientData()  {
    UserInfo::refreshData();
    if (!patientData) {
        throw std::runtime_error("Patient data is not initialized");
    }
    return *patientData;
}
void UserInfo::refreshData() {
    try {
        // Get the instance of DBManager
        DBManager& dbManager = DBManager::getInstance();

        if (!patientData) {
            throw std::runtime_error("Patient data is not initialized");
        }

        bsoncxx::document::view pData = patientData->view();
        auto room_number_element = pData["room_number"];
        auto patient_number_element = pData["patient_number"];

        if (room_number_element.type() == bsoncxx::type::k_utf8 && patient_number_element.type() == bsoncxx::type::k_utf8) {
            QString room_number = QString::fromUtf8(room_number_element.get_utf8().value.data(), room_number_element.get_utf8().value.size());
            QString patient_number = QString::fromUtf8(patient_number_element.get_utf8().value.data(), patient_number_element.get_utf8().value.size());

            auto maybe_result = dbManager.findPatient(room_number, patient_number);

            if (maybe_result) {
                patientData = std::make_unique<bsoncxx::document::value>(*maybe_result);
                UserInfo::getInstance()->setPatientData(std::move(patientData));
            } else {
                QMessageBox::warning(nullptr, "Login Error", "Incorrect room or patient number. Please enter valid credentials.");
            }
        } else {
            QMessageBox::warning(nullptr, "Data Error", "Missing or incorrect type for room number or patient number.");
        }
    } catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(nullptr, "Database Error", "Failed to connect to the database. Please check your connection settings.");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        QMessageBox::critical(nullptr, "Error", "An error occurred. Please try again.");
    }
}
