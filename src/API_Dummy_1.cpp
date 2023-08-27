#include <API_Dummy_1.hpp>

void API_Dummy_1::set_dictionary(Database::DictionaryId id)
{
    
}

Database::DictionaryId API_Dummy_1::get_dictionary_id()
{
    return Database::DictionaryId::SIZE;
}

std::vector<std::string> API_Dummy_1::get_definition_from_word(std::string word)
{
    return std::vector<std::string>();
}

void API_Dummy_1::set_favorite(std::string word, bool favorite)
{
}

std::vector<std::string> API_Dummy_1::get_favorites()
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_1::get_word_from_definition(std::string definition)
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_1::get_history()
{
    return std::vector<std::string>();
}

void API_Dummy_1::add_definition(std::string word, std::string definition)
{
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

std::vector<std::string> API_Dummy_1::quizz_1_word_4_definition()
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_1::get_random_definitions(int count)
{
    return std::vector<std::string>();
}

std::vector< std::string> API_Dummy_1::quizz_1_definition_4_word()
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_1::get_random_words(int count)
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_1::get_favorites_list()
{
    return std::vector<std::string>();
}
 bool API_Dummy_1:: is_favorite(std::string word)
 {
        return false;
 }