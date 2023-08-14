#include <API_Dummy_1.hpp>
#include <iostream>

API_Dummy_1::API_Dummy_1()
: dictionary_id(DictionaryId(0))
, dictionaries(DictionaryId::SIZE)
{
    for(auto& dictionary : dictionaries)
        dictionary = new PersistentTrie();
    for(int id = 0; id < DictionaryId::SIZE; ++id) {
        std::vector<std::pair<std::string, std::string>> values;
        // extract_from_json(values, database.get_dictionary(id));
        values.push_back(std::make_pair("word", "definition"));
        values.push_back(std::make_pair("word", "definition"));
        values.push_back(std::make_pair("word", "definition"));
        values.push_back(std::make_pair("word", "definition"));
        values.push_back(std::make_pair("word", "definition"));
        values.push_back(std::make_pair("word", "definition"));
        dictionaries[id]->initialize(values);
    }
}

void API_Dummy_1::extract_from_json(std::vector<std::pair<std::string, std::string>> &values, const Json::Value &json)
{
    for(auto& word : json) {
        std::string word_str = word["word"].asString();
        std::string definition_str = word["definition"].asString();
        values.push_back(std::make_pair(word_str, definition_str));
    }
}

API_Dummy_1::~API_Dummy_1()
{
    for(auto& dictionary : dictionaries)
        delete dictionary;
}

void API_Dummy_1::set_dictionary(DictionaryId id)
{
}

API::DictionaryId API_Dummy_1::get_dictionary_id()
{
    return dictionary_id;
}

std::vector<std::string> API_Dummy_1::get_definition_from_word(std::string word)
{
    return dictionaries[dictionary_id]->get_version(version)->search(word);
}

void API_Dummy_1::set_favorite(std::string word, bool favorite)
{
}

std::vector<std::string> API_Dummy_1::get_favorites()
{
    return std::vector<std::string>();
}

std::string API_Dummy_1::get_word_from_definition(std::string definition)
{
    return "";
}

std::vector<std::string> API_Dummy_1::get_history()
{
    return std::vector<std::string>();
}

void API_Dummy_1::add_definition(std::string word, std::string definition)
{
    dictionaries[dictionary_id]->insert(word, definition);
    version++;
}

void API_Dummy_1::edit_definition(std::string word, int editID, std::string definition)
{
}

void API_Dummy_1::delete_word(std::string word)
{
}

std::vector<API::VersionDescriptor> API_Dummy_1::get_versions()
{
    return std::vector<API::VersionDescriptor>();
}

void API_Dummy_1::set_version(int version)
{
}

std::pair<std::string, std::string> API_Dummy_1::get_random_word_and_definition()
{
    return std::pair<std::string, std::string>();
}

std::vector<std::string> API_Dummy_1::get_randome_definitions(int count)
{
    return std::vector<std::string>();
}

std::pair<std::string, std::string> API_Dummy_1::get_random_definition_and_word()
{
    return std::pair<std::string, std::string>();
}

std::vector<std::string> API_Dummy_1::get_randome_words(int count)
{
    return std::vector<std::string>();
}

Json::Value API_Dummy_1::to_json()
{
    Json::Value json = dictionaries[dictionary_id]->to_json();
    return json;
}