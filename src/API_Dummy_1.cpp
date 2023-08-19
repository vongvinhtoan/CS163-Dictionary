#include <API_Dummy_1.hpp>
#include <iostream>

API_Dummy_1::API_Dummy_1()
: dictionary_id(DictionaryId(0))
, dictionaries(DictionaryId::SIZE)
{
    for(auto& dictionary : dictionaries)
        dictionary = new PersistentTrie();

    for(int id = 0; id < 1; ++id) {
        std::vector<std::pair<std::string, std::string>> values;
        //extract_from_json(values, database.get_dataset( id));
        values.push_back(std::make_pair("word", "nghia"));
        values.push_back(std::make_pair("do you love", "yeu em"));
        values.push_back(std::make_pair("application", "ung dung"));
        values.push_back(std::make_pair("kinny", "vua"));
        values.push_back(std::make_pair("mouse", "chuot"));
        values.push_back(std::make_pair("anhaayyo", "xin chao VN"));
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

std::vector<std::string> API_Dummy_1::get_random_word_and_definition()
{
    std::vector<std::vector<std::string>>random;
    std::vector<std::string> result;
    
    for(int i=0;i<4;i++){
        random.push_back(get_random_words(0));
    }
   
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
           if(i!=j) result.push_back(compare_definiton_word(random[i],random[j]).first);
        }
    }
    result.push_back(random[3][random[3].size()-1]);
    return result;
    
}

std::vector<std::string> API_Dummy_1::get_random_definitions(int count)
{

    return std::vector<std::string>();
}

std::vector< std::string> API_Dummy_1::get_random_definition_and_word()
{
    std::vector<std::vector<std::string>>random;
    std::vector<std::string> result;
    
    for(int i=0;i<4;i++){
        random.push_back(get_random_words(0));
    }
   
    for(int i=0;i<4;i++){
        // for(int j=0;j<4;j++){
        //    if(i!=j) {
        //     while(random[i][random[i].size()-1].compare(random[j][random[j].size()-1])==0){
        //         random[j]=get_random_words(0);
        //     }
        //    }
        // }
        result.push_back(random[i][random[i].size()-1]);
        
    }
    result.push_back(random[3][0]);
    return result;
}

std::vector<std::string> API_Dummy_1::get_random_words(int count)
{
    return dictionaries[0]->get_version(version)->get_random_word_and_definition();
}

Json::Value API_Dummy_1::to_json()
{
    Json::Value json = dictionaries[0]->to_json();
    return json;
}

std::pair<std::string,std::string> API_Dummy_1:: compare_definiton_word(std::vector<std::string>& str1,std::vector<std::string> str2)
{
    int n1=str1.size();
    int n2=str2.size();
    if(str1[n1-1].compare(str2[n2-1])!=0){
        std::pair<std::string,std::string> result;
        result.first=str1[0];
        result.second=str1[n1-1];
        return result;
    }
    str1=dictionaries[0]->get_version(version)->get_random_word_and_definition();
    return compare_definiton_word(str1,str2);
    
}

