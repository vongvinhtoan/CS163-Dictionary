#include <Database.hpp>

Database::Database()
{
    Json::Reader reader;
    std::ifstream dataset_Eng_Eng_file(".\\data\\json\\dataset_Eng_Eng.json");
    std::ifstream dataset_Eng_Eng_favourite_file(".\\data\\json\\dataset_Eng_Eng_favourite.json");
    std::ifstream dataset_Eng_Vie_file(".\\data\\json\\dataset_Eng_Vie.json");
    std::ifstream dataset_Eng_Vie_favourite_file(".\\data\\json\\dataset_Eng_Vie_favourite.json");
    std::ifstream dataset_Vie_Eng_file(".\\data\\json\\dataset_Vie_Eng.json");
    std::ifstream dataset_Vie_Eng_favourite_file(".\\data\\json\\dataset_Vie_Eng_favourite.json");
    std::ifstream dataset_Emoji_file(".\\data\\json\\dataset_Emoji.json");
    std::ifstream dataset_Slang_Word_file(".\\data\\json\\dataset_Slang_Word.json");
    std::ifstream dataset_history_file(".\\data\\json\\dataset_history.json");

    reader.parse(dataset_Eng_Eng_file, dataset_Eng_Eng);
    reader.parse(dataset_Eng_Eng_favourite_file, dataset_Eng_Eng_favourite);
    reader.parse(dataset_Eng_Vie_file, dataset_Eng_Vie);
    reader.parse(dataset_Eng_Vie_favourite_file, dataset_Eng_Vie_favourite);
    reader.parse(dataset_Vie_Eng_file,dataset_Vie_Eng);
    reader.parse(dataset_Vie_Eng_favourite_file,dataset_Vie_Eng_favourite);
    reader.parse(dataset_Emoji_file,dataset_Emoji);
    reader.parse(dataset_history_file,dataset_history);
    
}



Database::~Database()
{
}