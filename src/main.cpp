#include <Application.hpp>
#include <iostream>
#include <API_Dummy_1.hpp>

int main()
{
    // try
    // {
    //     Application application;
    //     application.run();
    // }
    // catch (std::exception& e)
    // {
    //     std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    // }
    srand((unsigned)time(NULL));
    API* api = new API_Dummy_1();
    
    api->set_dictionary(Database::DictionaryId::ENG_ENG);
    std::cout<<"Dictionary: "<<std::endl;

    
    Json::Value json = ((API_Dummy_1*)api)->to_json();
    

    // PersistentTrie* trie = new PersistentTrie();
    // std::vector<std::pair<std::string, std::string>> values = {
    //     {"a", "b"},
    //     {"c", "d"},
    //     {"e", "f"},
    // };
    // trie->initialize(values);
    // std::cout<<"Dictionary: "<<std::endl;
    // Json::Value json = trie->to_json();
    // std::ofstream file("data.json");
    // file << json;
    // file.close();

    PersistentTrie* trie2 = new PersistentTrie();
    trie2->init_json(json);
    std::cout<<"Dictionary: "<<std::endl;
    std::vector<std::string> definitions = trie2->get_version(1)->search("aaaaaaaaaaaaaaaaaaa");
    std::cout<<"definitions.size() = "<<definitions.size()<<std::endl;
    for (auto definition : definitions) {
        std::cout<<"---------------------\n";
        std::cout<<definition<<std::endl;
    }
    api->set_favorite("a",true);
    api->set_favorite("b",true);
    api->set_favorite("car",true);
    api->set_favorite("dog",true);
    std::ofstream file("data.json");
    file << json;
    file.close();
    std::vector<API::VersionDescriptor> a=api->get_versions();
    for(auto i:a){
        std::cout<<i.version<<" "<<i.description<<std::endl;
    }
    std::vector<std::string>s=api->get_random_definitions(0);
    for(auto i:s){
        std::cout<<i<<std::endl;
    }
    delete api;
    return 0;    
    //Json::Value json = ((API_Dummy_1*)api)->to_json();
    
    // while (true){
    //     std::string word;
    //     std::cout<<"Enter word: ";
    //     std:: cin>>word;
    //     std::vector<std::string> definitions = api->get_definition_from_word( word);
        
    //     //std::cout<<"Definitions: \n";
    //     for (auto definition : definitions) {
    //         std::cout<<"---------------------\n";
    //         std::cout<<definition<<std::endl;
    //     }
    // }
    // delete api;
    return 0;
}