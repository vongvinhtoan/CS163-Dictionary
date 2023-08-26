#include <API_Dummy_0.hpp>
#include <Randomizer.hpp>
#include <iostream>

void API_Dummy_0::set_dictionary(Database::DictionaryId id)
{
    std::cout<<"API_Dummy_0::set_dictionary: "<<id<<std::endl;
    dictionaryId = id;
}

Database::DictionaryId API_Dummy_0::get_dictionary_id()
{
    std::cout<<"API_Dummy_0::get_dictionary_id: "<<dictionaryId<<std::endl;
    return dictionaryId;
}

std::vector<std::string> API_Dummy_0::get_definition_from_word(std::string word)
{
    std::cout<<"API_Dummy_0::get_definition_from_word: "<<word<<std::endl;
    std::vector<std::string> definitions;
    Randomizer &randomizer = Randomizer::getInstance();
    int count = randomizer.nextInt(0, 5);
    count = randomizer.nextInt(0, count);
    for (int i = 0; i < count; i++)
    {
        definitions.push_back("definition " + std::to_string(i));
    }
    return definitions;
}

void API_Dummy_0::set_favorite(std::string word, bool favorite)
{
    std::cout<<"API_Dummy_0::set_favorite: "<<word<<", "<<favorite<<std::endl;
}

std::vector<std::string> API_Dummy_0::get_favorites()
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_0::get_word_from_definition(std::string definition)
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_0::get_history()
{
    return std::vector<std::string>();
}

void API_Dummy_0::add_definition(std::string word, std::string definition)
{
}

void API_Dummy_0::edit_definition(std::string word, int editID, std::string definition)
{
}

void API_Dummy_0::delete_word(std::string word)
{
}

std::vector<API::VersionDescriptor> API_Dummy_0::get_versions()
{
    return std::vector<API::VersionDescriptor>();
}

void API_Dummy_0::set_version(int version)
{
}

std::vector<std::string> API_Dummy_0::quizz_1_word_4_definition()
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_0::get_random_definitions(int count)
{
    return std::vector<std::string>();
}

std::vector< std::string> API_Dummy_0::quizz_1_definition_4_word()
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_0::get_random_words(int count)
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_0::get_favorites_list()
{
    return std::vector<std::string>();
}
 bool API_Dummy_0:: is_favorite(std::string word)
 {
        return false;
 }