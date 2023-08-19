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

    api->add_definition("fuck", "concu");
    api->add_definition("australia","hi hi");
    Json::Value json = ((API_Dummy_1*)api)->to_json();
    
    std::ofstream file("database.json");
    file << json;
    file.close();    
        std::vector<std::string> definitions = api->get_random_word_and_definition();
        
        //std::cout<<"Definitions: \n";
        for (auto definition : definitions) {
            std::cout<<definition<<std::endl;
        }
        

    delete api;
    return 0;
}