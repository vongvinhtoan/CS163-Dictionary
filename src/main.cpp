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
    int n;
    std::cout<<"Enter n: ";
    std::cin>>n;
    std::vector<std::string> words= api->get_random_words(n); 
           
        // words.push_back(api->get_random_words(n).back());
    // std::string x;
    // std::cout<<"Enter word: ";
    // std::cin>>x;
    // if(api->is_favorite(x)==true)
    //     std::cout<<"true"<<std::endl;
    //     else std::cout<<"false"<<std::endl;
    //  for(auto x:words)
    //      api->set_favorite(x, true);

    // std::vector<std::string> s = api->get_favorites_list();
     for(auto u:words) std::cout<<u<<std::endl;
    
   for(int i=0;i<n;i++){
    api->delete_word(words[i]);
   }
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