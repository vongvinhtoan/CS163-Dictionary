#include <API_Dummy_0.hpp>

void API_Dummy_0::set_dictionary(DictionaryId id)
{
}

API::DictionaryId API_Dummy_0::get_dictionary_id()
{
    return DictionaryId::NONE;
}

std::vector<std::string> API_Dummy_0::get_definition_from_word(std::string word)
{
    return std::vector<std::string>();
}

void API_Dummy_0::set_favorite(std::string word, bool favorite)
{
}

std::vector<std::string> API_Dummy_0::get_favorites()
{
    return std::vector<std::string>();
}

std::string API_Dummy_0::get_word_from_definition(std::string definition)
{
    return "";
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

std::pair<std::string, std::string> API_Dummy_0::get_random_word_and_definition()
{
    return std::pair<std::string, std::string>();
}

std::vector<std::string> API_Dummy_0::get_randome_definitions(int count)
{
    return std::vector<std::string>();
}

std::pair<std::string, std::string> API_Dummy_0::get_random_definition_and_word()
{
    return std::pair<std::string, std::string>();
}

std::vector<std::string> API_Dummy_0::get_randome_words(int count)
{
    return std::vector<std::string>();
}