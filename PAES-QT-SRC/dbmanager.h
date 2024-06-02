#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <memory>
#include <QString>

class DBManager {
public:
    static DBManager& getInstance();
    std::unique_ptr<bsoncxx::document::value> findPatient(const QString& room_number, const QString& patient_number);

private:
    DBManager(); // Constructor is private for singleton
    ~DBManager(); // Destructor
    DBManager(const DBManager&) = delete; // Prevent copying
    DBManager& operator=(const DBManager&) = delete; // Prevent assignment

    mongocxx::instance instance; // MongoDB instance
    mongocxx::client client; // MongoDB client
};

#endif // DBMANAGER_H
