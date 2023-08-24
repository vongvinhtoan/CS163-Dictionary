#include <API_Dummy_1.hpp>
#include <iostream>


int holder=1;
API_Dummy_1::API_Dummy_1()
: dictionary_id(Database::DictionaryId::ENG_ENG)
, datasets(Database::DictionaryId::SIZE)
, version(0)
{
    for(int id = 0; id < Database::DictionaryId::SIZE; id++) {
        datasets[id].dictionary = build_trie_from_value(database.get_dataset(static_cast<Database::DictionaryId>(id)));
        datasets[id].favorite = new PersistentTrie();
    }
}

PersistentTrie* API_Dummy_1::build_trie_from_value(Json::Value dictionary)
{
    PersistentTrie* res = new PersistentTrie();
    std::vector<std::pair<std::string, std::string>> values;
    extract_from_json(values, dictionary);
    res->initialize(values);

    return res;
}

void API_Dummy_1::extract_from_json(std::vector<std::pair<std::string, std::string>> &values, const Json::Value &json)
{
    for(auto& word : json) {
        std::string word_str = word["word"].asString();
        std::string definition_str = word["definition"].asString();
        std::string definition_temp;
        std::stringstream ss(definition_str);
        while(std::getline(ss,definition_temp,'|')){
          values.push_back(std::make_pair(word_str, definition_temp));
        }
    }
}

API_Dummy_1::~API_Dummy_1()
{
    
}

void API_Dummy_1::set_dictionary(Database::DictionaryId id)
{
    dictionary_id = id;
}

Database::DictionaryId API_Dummy_1::get_dictionary_id()
{

   return Database::DictionaryId::SIZE;
}

std::vector<std::string> API_Dummy_1::get_definition_from_word(std::string word)
{
    history.push_back(word);
    return datasets[holder].dictionary->get_version(version)->search(word);
}

void API_Dummy_1::set_favorite(std::string word, bool favorite)
{

}

std::vector<std::string> API_Dummy_1::get_favorites()
{
     return datasets[holder].favorite->get_version(version)->dfs();
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
    datasets[holder].add_definition(word,definition);
}

void API_Dummy_1::edit_definition(std::string word, int editID, std::string definition)
{
    
}

void API_Dummy_1::delete_word(std::string word)
{
    datasets[holder].delete_word(word);
    version++;
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
    std::vector<std::vector<std::string>>random;
    std::vector<std::string> result;
    for(int i=0;i<4;i++){
        random.push_back(get_random_words(0));
    }
     for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
           if(i!=j) {
            while(random[i][random[i].size()-1].compare(random[j][random[j].size()-1])==0){
                random[j]=get_random_words(0);
            }
           }
        }
        result.push_back(random[i][0]);
        
    }
    result.push_back(random[3][random[3].size()-1]);
    return result;
    
}

std::vector<std::string> API_Dummy_1::get_random_definitions(int count)
{

    return std::vector<std::string>();
}

std::vector< std::string> API_Dummy_1::quizz_1_definition_4_word()
{
    std::vector<std::vector<std::string>>random;
    std::vector<std::string> result;
    
    for(int i=0;i<4;i++){
        random.push_back(get_random_words(0));
    }
   
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
           if(i!=j) {
            while(random[i][random[i].size()-1].compare(random[j][random[j].size()-1])==0){
                random[j]=get_random_words(0);
            }
           }
        }
        result.push_back(random[i][random[i].size()-1]);
        
    }
    result.push_back(random[3][0]);
    return result;
}

std::vector<std::string> API_Dummy_1::get_random_words(int count)
{
    std::vector<std::string> word_and_definition;
    for(int i=0;i<count;i++){
        word_and_definition.insert(word_and_definition.end()
        ,datasets[holder].dictionary->get_version(version)->get_random_word().begin()
        ,datasets[holder].dictionary->get_version(version)->get_random_word().end());
    }
    return word_and_definition;
}

Json::Value API_Dummy_1::to_json()
{
    Json::Value json = datasets[dictionary_id].dictionary->to_json();
    return json;
}

 void API_Dummy_1:: add_favorite(std::string word)
 {
    datasets[holder].add_favorite(word);
    version++;
 }
void API_Dummy_1:: delete_favorite(std::string word)
{
    datasets[holder].delete_favorite(word);
    version++;
}
std::vector<std::string>API_Dummy_1:: dfs_favourite()
{
    return datasets[holder].favorite->get_version(version)->dfs();
    
}