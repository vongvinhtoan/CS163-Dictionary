#pragma once

class Database {
public:
    static Database& get_instance() {
        static Database instance;
        return instance;
    }

    // Other public methods...

private:
    Database() {} // Private constructor
    Database(const Database&) = delete; // Delete copy constructor
    Database& operator=(const Database&) = delete; // Delete copy assignment operator
};


