#include <API_Dummy_1.hpp>

API_Dummy_1::API_Dummy_1()
{
    PersistentTrie datasets[Database::DictionaryId::SIZE];
    for(int id = 0; id < Database::DictionaryId::SIZE; id++) {
        datasets[id] = build_trie_from_value(database.get_dataset(static_cast<Database::DictionaryId>(id)));
    }
}

PersistentTrie API_Dummy_1::build_trie_from_value(Json::Value dictionary)
{
    PersistentTrie res;
    for(Json::Value item: dictionary)
    {
        std::string word = item["word"].asString();
        std::string definition = item["definition"].asString();

        res.insert(word, definition);
    }

    return res;
}

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