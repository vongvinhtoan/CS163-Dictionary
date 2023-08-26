#pragma once

#include <Database.hpp>
#include <string>
#include <vector>

class API
{
public:
    struct VersionDescriptor
    {
        int version;
        std::string description;
    };
    
protected:
    Database &database;

public:
    API() : database(Database::get_instance()) {}
    
public:
    virtual void set_dictionary(Database::DictionaryId id) = 0;
    virtual Database::DictionaryId get_dictionary_id() = 0; 
    virtual std::vector<std::string> get_definition_from_word(std::string word) = 0;
    virtual void set_favorite(std::string word, bool favorite) = 0;
    virtual std::vector<std::string> get_favorites() = 0;
    virtual std::vector<std::string> get_word_from_definition(std::string definition) = 0;
    virtual std::vector<std::string> get_history() = 0;
    virtual void add_definition(std::string word, std::string definition) = 0;
    virtual void edit_definition(std::string word, int editID, std::string definition) = 0;
    virtual void delete_word(std::string word) = 0;
    virtual std::vector<VersionDescriptor> get_versions() = 0;
    virtual void set_version(int version) = 0;
    virtual std::vector<std::string> quizz_1_word_4_definition() = 0;
    virtual std::vector<std::string> get_random_definitions(int count) = 0;
    virtual std::vector<std::string> quizz_1_definition_4_word() = 0;
    virtual std::vector<std::string> get_random_words(int count) = 0;
    virtual std::vector<std::string> get_favorites_list()=0;
    virtual bool is_favorite(std::string word)=0;

};