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

    API* api = new API_Dummy_1();

    api->add_definition("meomeo", "concu");

    Json::Value json = ((API_Dummy_1*)api)->to_json();
    
    std::ofstream file("database.json");
    file << json;
    file.close();

    while(true)
    {
        std::cout<<"Enter a word: ";
        std::string word;
        std::cin>>word;
        std::vector<std::string> definitions = api->get_definition_from_word(word);
        std::cout<<"Definitions: \n";
        for (auto definition : definitions)
        {
            std::cout<<definition<<std::endl;
        }
    }

    delete api;
    return 0;
}