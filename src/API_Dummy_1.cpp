#include <API_Dummy_1.hpp>
#include <iostream>

// API_Dummy_1::API_Dummy_1()
// : dictionary_id(DictionaryId())
// , dictionaries(DictionaryId::SIZE)
// {
//     for(auto& dictionary : dictionaries)
//         dictionary = new PersistentTrie();

//     for(int id = 0; id <1 ; ++id) {
//         std::vector<std::pair<std::string, std::string>> values;
//         //extract_from_json(values, database.get_dataset( id));
//         values.push_back(std::make_pair("word", "nghia"));
//         values.push_back(std::make_pair("do you love", "yeu em"));
//         values.push_back(std::make_pair("application", "ung dung"));
//         values.push_back(std::make_pair("kinny", "vua"));
//         values.push_back(std::make_pair("mouse", "chuot"));
//         values.push_back(std::make_pair("anhaayyo", "xin chao VN"));
//         dictionaries[id]->initialize(values);
//     }
// }
int holder=2;
API_Dummy_1::API_Dummy_1()
: dictionary_id(Database::DictionaryId::ENG_ENG)
, dictionaries(Database::DictionaryId::SIZE)
, version(0)
{
    for(int id = 0; id < Database::DictionaryId::SIZE; id++) {
        dictionaries[id] = build_trie_from_value(database.get_dataset(static_cast<Database::DictionaryId>(id)));
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
    for(auto& dictionary : dictionaries)
        delete dictionary;
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
    return dictionaries[Database::DictionaryId::ENG_ENG]->get_version(version)->search(word);
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
    dictionaries[0]->insert(word, definition);
    version++;
}

void API_Dummy_1::edit_definition(std::string word, int editID, std::string definition)
{
    
}

void API_Dummy_1::delete_word(std::string word)
{
    dictionaries[0]->delete_word(word);
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
    return dictionaries[dictionary_id]->get_version(version)->get_random_word();
}

Json::Value API_Dummy_1::to_json()
{
    Json::Value json = dictionaries[dictionary_id]->to_json();
    return json;
}

 
