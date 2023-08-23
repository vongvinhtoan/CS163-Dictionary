#pragma once

#include <API.hpp>
#include <PersistentTrie.hpp>
#include <Trie.hpp>

class API_Dummy_1 : public API
{
private:
    int version;
    Database::DictionaryId dictionary_id;
    std::vector<PersistentTrie*> dictionaries;
    

private:
    void extract_from_json(std::vector<std::pair<std::string, std::string>> &values, const Json::Value &json);
    PersistentTrie* build_trie_from_value(Json::Value dictionary);

public:
    API_Dummy_1();
    ~API_Dummy_1();

public:
    virtual void set_dictionary(Database::DictionaryId id);
    virtual Database::DictionaryId get_dictionary_id(); 
    virtual std::vector<std::string> get_definition_from_word(std::string word);
    virtual void set_favorite(std::string word, bool favorite);
    virtual std::vector<std::string> get_favorites();
    virtual std::vector<std::string> get_word_from_definition(std::string definition);
    virtual std::vector<std::string> get_history();
    virtual void add_definition(std::string word, std::string definition);
    virtual void edit_definition(std::string word, int editID, std::string definition);
    virtual void delete_word(std::string word);
    virtual std::vector<VersionDescriptor> get_versions();
    virtual void set_version(int version);
    virtual std::vector<std::string> quizz_1_word_4_definition();
    virtual std::vector<std::string> get_random_definitions(int count);
    virtual std::vector<std::string> quizz_1_definition_4_word();
    virtual std::vector<std::string> get_random_words(int count);
    Json::Value to_json();
    
};