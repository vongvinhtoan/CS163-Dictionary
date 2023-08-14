#include <Database.hpp>

Database::Database()
{
    Json::Reader reader;
    std::ifstream dataset_Eng_Eng_file(".\\data\\json\\dataset_Eng_Eng.json");
    std::ifstream dataset_Eng_Vie_file(".\\data\\json\\dataset_Eng_Vie.json");
    std::ifstream dataset_Vie_Eng_file(".\\data\\json\\dataset_Vie_Eng.json");
    std::ifstream dataset_Emoji_file(".\\data\\json\\dataset_Emoji.json");
    std::ifstream dataset_Slang_Word_file(".\\data\\json\\dataset_Slang_Word.json");

    reader.parse(dataset_Eng_Eng_file, dataset_Eng_Eng);
    reader.parse(dataset_Eng_Vie_file, dataset_Eng_Vie);
    reader.parse(dataset_Vie_Eng_file,dataset_Vie_Eng);
    reader.parse(dataset_Emoji_file,dataset_Emoji);
    reader.parse(dataset_Slang_Word_file,dataset_Slang_Word);
}

Json::Value Database::get_dataset(std:: string dataset_name){
    Json::Value dataset;
    if(dataset_name == "Eng_Eng"){
        dataset = dataset_Eng_Eng;
    }else if(dataset_name == "Eng_Vie"){
        dataset = dataset_Eng_Vie;
    }else if(dataset_name == "Vie_Eng"){
        dataset = dataset_Vie_Eng;
    }else if(dataset_name == "Emoji"){
        dataset = dataset_Emoji;
    }else if(dataset_name == "Slang_Word"){
        dataset= dataset_Slang_Word;
    }else {
        return Json::Value();
    }

    return dataset;
}

Database::~Database()
{
}