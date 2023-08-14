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

    for(Json::Value item: dataset_Eng_Eng) {
        std::string word = item["word"].asString();
        std::string definition = item["definition"].asString();

    }
}

Json::Value Database::get_dataset(API::DictionaryId id){
    if(id == API::DictionaryId::EMOJI) return dataset_Emoji;
}

Database::~Database()
{
}