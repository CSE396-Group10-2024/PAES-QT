#ifndef MONGOINSTANCE_H
#define MONGOINSTANCE_H
#include <mongocxx/instance.hpp>

class MongoInstance {
public:
    static mongocxx::instance& get_instance() {
        static mongocxx::instance inst;
        return inst;
    }

private:
    MongoInstance() {} // Constructor is private
};

// Usage:
void function() {
    auto& instance = MongoInstance::get_instance();
    // Now you can use 'instance' to work with MongoDB
}

#endif // MONGOINSTANCE_H
