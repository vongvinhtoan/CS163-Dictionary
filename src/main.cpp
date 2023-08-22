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
   
    Json::Value json = ((API_Dummy_1*)api)->to_json();
    
    std::ofstream file("database.json");
    file << json;
    file.close();    
    while (true){
        std::string word;
        std::cout<<"Enter word: ";
        std:: cin>>word;
        std::vector<std::string> definitions = api->get_definition_from_word( word);
        
        //std::cout<<"Definitions: \n";
        for (auto definition : definitions) {
            std::cout<<"---------------------\n";
            std::cout<<definition<<std::endl;
        }
    }
        
        

    delete api;
    return 0;
}