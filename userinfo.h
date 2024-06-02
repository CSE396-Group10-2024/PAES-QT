#ifndef USER_INFO_H
#define USER_INFO_H

#include <memory>
#include <bsoncxx/document/value.hpp>
#include <QString>
#include <bsoncxx/builder/basic/document.hpp>
#include <QMessageBox>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>
class UserInfo {
private:
    static UserInfo* instance;
    std::unique_ptr<bsoncxx::document::value> patientData;

    UserInfo();  // Private constructor

public:
    static UserInfo* getInstance();

    UserInfo(const UserInfo&) = delete;
    UserInfo& operator=(const UserInfo&) = delete;
    UserInfo(UserInfo&&) = delete;
    UserInfo& operator=(UserInfo&&) = delete;
    QString getColorForExercise(const QString& exerciseType);
    void setPatientData(std::unique_ptr<bsoncxx::document::value> data);
    const bsoncxx::document::value& getPatientData() ;
    void refreshData() ;  // Example method to refresh data
};

#endif // USER_INFO_H
