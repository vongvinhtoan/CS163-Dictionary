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
    std::ifstream dataset_Emoji_favourite_file(".\\data\\json\\dataset_Emoji_favourite.json");
    std::ifstream dataset_Slang_Word_file(".\\data\\json\\dataset_Slang_Word.json");
    std::ifstream dataset_Slang_Word_favourite_file(".\\data\\json\\dataset_Slang_Word_favourite.json");
    std::ifstream dataset_history_file(".\\data\\json\\dataset_history.json");




    reader.parse(dataset_Eng_Eng_file, dataset_Eng_Eng);
    reader.parse(dataset_Eng_Eng_favourite_file, dataset_Eng_Eng_favourite);

    reader.parse(dataset_Eng_Vie_file, dataset_Eng_Vie);
    reader.parse(dataset_Eng_Vie_favourite_file, dataset_Eng_Vie_favourite);

    reader.parse(dataset_Vie_Eng_file,dataset_Vie_Eng);
    reader.parse(dataset_Vie_Eng_favourite_file,dataset_Vie_Eng_favourite);

    reader.parse(dataset_Emoji_file,dataset_Emoji);
    reader.parse(dataset_Emoji_favourite_file,dataset_Emoji_favourite);

    reader.parse(dataset_Slang_Word_file,dataset_Slang_Word);
    reader.parse(dataset_Slang_Word_favourite_file,dataset_Slang_Word_favourite);
}

Json::Value Database::get_dataset(DictionaryId id){
    if     (id == DictionaryId::EMOJI) return dataset_Emoji;
    else if(id == DictionaryId::ENG_ENG) return dataset_Eng_Eng;
    else if(id == DictionaryId::ENG_VIET) return dataset_Eng_Vie;
    else if(id == DictionaryId::VIET_ENG) return dataset_Vie_Eng;
    else if(id == DictionaryId::SLANG_WORD) return dataset_Slang_Word;
    else if(id == DictionaryId::ENG_ENG_FAVOURITE) return dataset_Eng_Eng_favourite;
    else if(id == DictionaryId::ENG_VIET_FAVOURITE) return dataset_Eng_Vie_favourite;
    else if(id == DictionaryId::VIET_ENG_FAVOURITE) return dataset_Vie_Eng_favourite;
    else if(id == DictionaryId::SLANG_WORD_FAVOURITE) return dataset_Slang_Word_favourite;
    else if(id == DictionaryId::EMOJI_FAVOURITE) return dataset_Emoji_favourite;
    else if(id == DictionaryId::HISTORY) return dataset_history;
    else return Json::Value();
    
}


Database::~Database()
{
}