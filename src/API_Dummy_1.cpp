#include <API_Dummy_1.hpp>
#include <iostream>


API_Dummy_1::API_Dummy_1()
: dictionary_id(Database::DictionaryId::SIZE)
, datasets(Database::DictionaryId::SIZE)
, version(0)
{
    for(int id = 0; id < Database::DictionaryId::SIZE; id++) {
      

        datasets[id].dictionary = build_trie_from_value(database.get_dataset((Database::DictionaryId)(id)));
        //datasets[id].dictionary=build_trie_from_json( database.get_dataset((Database::DictionaryId)(id))["dictionary"]);
        std::vector<std::pair<std::string, std::string>> values(0);
        datasets[id].favorite->initialize(values);
        //datasets[id].favorite=build_trie_from_json(database.get_dataset((Database::DictionaryId)(id))["favorite"]);
    }
    version++;
}

PersistentTrie* API_Dummy_1::build_trie_from_value(Json::Value dictionary)
{
    PersistentTrie* res = new PersistentTrie();
    std::vector<std::pair<std::string, std::string>> values;
    extract_from_json(values, dictionary);
    res->initialize(values);
    return res;
}

PersistentTrie* API_Dummy_1::build_trie_from_json(Json:: Value dictionary)
{
    PersistentTrie* res = new PersistentTrie();
    res->init_json(dictionary);
    return res;
}
void API_Dummy_1::extract_from_json(std::vector<std::pair<std::string, std::string>> &values, const Json::Value &json)
{
    
    for(auto& word : json ) {
        std::string word_str = word["word"].asString();
        std::string definition_str = word["definition"].asString();
        std::string definition_temp;
        std::stringstream ss(definition_str);
        while(std::getline(ss,definition_temp,'|')){
          values.push_back(std::make_pair(word_str, definition_temp));
        }
    }
    return ;
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
    return datasets[dictionary_id].dictionary->get_version(version)->search(word);
}

void API_Dummy_1::set_favorite(std::string word, bool favorite)
{
    if(favorite==false) {
        delete_favorite(word);
    }
    else {
        add_favorite(word);
    }
    return;
}

void API_Dummy_1::delete_favorite(std::string word)
{
    datasets[dictionary_id].delete_favorite(word);
    version++;
}

void API_Dummy_1::add_favorite(std::string word)
{
    if(datasets[dictionary_id].dictionary->get_version(version)->check_exist(word)) return;
    datasets[dictionary_id].add_favorite(word);
    version++;
}

std::vector<std::string> API_Dummy_1::get_favorites()
{
    return datasets[dictionary_id].favorite->get_version(version)->dfs();
    
}

std::vector<std::string> API_Dummy_1::get_word_from_definition(std::string definition)
{
    return std::vector<std::string>();
}

std::vector<std::string> API_Dummy_1::get_history()
{
    
    return history;
}

void API_Dummy_1::add_definition(std::string word, std::string definition)
{
    datasets[dictionary_id].add_definition(word,definition);
    version++;
}

void API_Dummy_1::edit_definition(std::string word, int editID, std::string definition)
{
    datasets[dictionary_id].edit_definition(word,editID,definition);
    version++;
     
}

void API_Dummy_1::delete_word(std::string word)
{
    datasets[dictionary_id].delete_word(word);
    version++;
}

std::vector<API::VersionDescriptor> API_Dummy_1::get_versions()
{ 
    std::vector<API::VersionDescriptor> result;
    API::VersionDescriptor tmp;
    tmp.version=0;
    tmp.description="Initial version";
    result.push_back(tmp);
    tmp.version=1;
    tmp.description="Last version";
    for(int i=2;i<=version;i++){
        API::VersionDescriptor temp;
        temp.version=i;
        if(datasets[dictionary_id].favorite->get_version(i)->get_version_description().compare
        (datasets[dictionary_id].favorite->get_version(i-1)->get_version_description())!=0){
            temp.description="Favourite list "+datasets[dictionary_id].favorite->get_version(i)->get_version_description();
        }
        else{
            temp.description="Dictionary "+datasets[dictionary_id].dictionary->get_version(i)->get_version_description();
        }
        result.push_back(temp);

    }
    return result;
}

void API_Dummy_1::set_version(int version)
{
    this->version = version;
}

std::vector<std::string> API_Dummy_1::quizz_1_word_4_definition()
{
    std::vector<std::vector<std::string>>random;
    std::vector<std::string> result;
    for(int i=0;i<4;i++){
        random.push_back(get_random_words_and_definition());
    }

     for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
           if(i!=j && random[i][random[i].size()-1].compare(random[j][random[j].size()-1])==0){
                random[i]=get_random_words_and_definition();
                j=0;
            }
       }
        result.push_back(random[i][0]);
    }

    result.push_back(random[3][random[3].size()-1]);
    return result;
}

std::vector<std::string> API_Dummy_1::quizz_1_definition_4_word()
{
    std::vector<std::vector<std::string>>random;
    std::vector<std::string> result;
    
    for(int i=0;i<4;i++)  random.push_back(get_random_words_and_definition());
   
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i!=j &&random[i][random[i].size()-1].compare(random[j][random[j].size()-1])==0){
                random[i]=get_random_words_and_definition();
                j=0;
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
    std::vector<std::string> result;
    for(int i=0;i<count;i++)    
        word_and_definition.push_back(get_random_words_and_definition().back());
    
    for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            if(i!=j && word_and_definition[i].compare(word_and_definition[j])==0){
                word_and_definition[i]=get_random_words_and_definition().back();
                j=0;
            }
        }
    }
    return word_and_definition;
}

Json::Value API_Dummy_1::to_json()
{
    return datasets[dictionary_id].dictionary->to_json();
}


std::vector<std::string> API_Dummy_1::get_favorites_list()
{
    return datasets[dictionary_id].favorite->get_version(version)->dfs();
}
 
bool API_Dummy_1::is_favorite(std::string word)
{
    return datasets[dictionary_id].favorite->get_version(version)->check_exist(word);
}
 
std::vector<std::string> API_Dummy_1:: get_random_words_and_definition(){
    return datasets[dictionary_id].dictionary->get_version(version)->get_random_word();
}

void API_Dummy_1::serialize()
{
    std::string str1=datasets[dictionary_id].dictionary->get_version(version)->serialize();
    std::string str2=datasets[dictionary_id].favorite->get_version(version)->serialize();
    std::ofstream fout("data.txt");
    fout<<str1<<std::endl;
    //file<<str2<<std::endl;
    fout.close();

}

 std::vector<std::string>API_Dummy_1:: get_random_definitions(int count){
    std::vector<std::string> s;
    s.push_back(get_random_words_and_definition().front()) ;
    s.push_back(get_random_words_and_definition().back());
    return s;
}
//từ đầu là definition
//từ cuối là word