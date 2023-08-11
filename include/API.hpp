#pragma once

#include <Database.hpp>
#include <string>
#include <vector>

class API
{
public:
    enum DictionaryId {
        VIET_ENG,
        ENG_ENG,
        ENG_VIET,
        EMOJI,
        SIZE
    };
    
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
    virtual void set_dictionary(DictionaryId id) = 0;
    virtual DictionaryId get_dictionary_id() = 0;
    virtual std::vector<std::string> get_definition_from_word(std::string word) = 0;
    virtual void set_favorite(std::string word, bool favorite) = 0;
    virtual std::vector<std::string> get_favorites() = 0;
    virtual std::string get_word_from_definition(std::string definition) = 0;
    virtual std::vector<std::string> get_history() = 0;
    virtual void add_definition(std::string word, std::string definition) = 0;
    virtual void edit_definition(std::string word, int editID, std::string definition) = 0;
    virtual void delete_word(std::string word) = 0;
    virtual std::vector<VersionDescriptor> get_versions() = 0;
    virtual void set_version(int version) = 0;
    virtual std::pair<std::string, std::string> get_random_word_and_definition() = 0;
    virtual std::vector<std::string> get_randome_definitions(int count) = 0;
    virtual std::pair<std::string, std::string> get_random_definition_and_word() = 0;
    virtual std::vector<std::string> get_randome_words(int count) = 0;
};