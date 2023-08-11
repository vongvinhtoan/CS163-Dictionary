#pragma once

#include <json.h>
#include <fstream>

class Database {
private:
    // Variables
    Json::Value dataset_Eng_Eng;
    Json::Value dataset_Eng_Vie;

public:
    Json::Value get_dataset(std::string dataset_name);  

public:
    static Database& get_instance() {
        static Database instance;
        return instance;
    }
    ~Database();

private:
    Database() {} // Private constructor
    Database(const Database&) = delete; // Delete copy constructor
    Database& operator=(const Database&) = delete; // Delete copy assignment operator
};