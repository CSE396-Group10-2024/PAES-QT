#include "dbmanager.h"
#include <mongocxx/exception/exception.hpp>
#include <QMessageBox>
#include <iostream>

DBManager::DBManager()
    : instance{},
    client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}}
//const auto uri = mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"};

{
    // Initialize any other members if needed
}

DBManager::~DBManager() {
    // Clean up resources if necessary
}

DBManager& DBManager::getInstance() {
    static DBManager instance; // Guaranteed to be destroyed and instantiated on first use
    return instance;
}

std::unique_ptr<bsoncxx::document::value> DBManager::findPatient(const QString& room_number, const QString& patient_number) {
    try {
        auto collection = client["paes"]["patients"];
        bsoncxx::builder::basic::document filter_builder;
        filter_builder.append(bsoncxx::builder::basic::kvp("room_number", room_number.toStdString()),
                              bsoncxx::builder::basic::kvp("patient_number", patient_number.toStdString()));

        auto result = collection.find_one(filter_builder.view());
        if (result) {
            return std::make_unique<bsoncxx::document::value>(result->view());
        }
    } catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB Error: " << e.what() << std::endl;
        QMessageBox::critical(nullptr, "Database Error",
                              "Failed to connect to the database. Please check your connection settings.");
    }
    return nullptr;
}

