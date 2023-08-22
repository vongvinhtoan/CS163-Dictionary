#pragma once

#include <json.h>
#include <fstream>


class Database {

    public:
    enum DictionaryId {
        VIET_ENG,
        VIET_ENG_FAVOURITE,
        ENG_ENG,
        ENG_ENG_FAVOURITE,
        ENG_VIET,
        ENG_VIET_FAVOURITE,
        EMOJI,
        EMOJI_FAVOURITE,
        SLANG_WORD,
        SLANG_WORD_FAVOURITE,
        HISTORY,
        SIZE
    };

private:
    // Variables
    Json::Value dataset_Eng_Eng;
    Json::Value dataset_Eng_Eng_favourite;
  
    Json::Value dataset_Eng_Vie;
    Json::Value dataset_Eng_Vie_favourite;

    Json::Value dataset_Vie_Eng;
    Json::Value dataset_Vie_Eng_favourite;
 
    Json::Value dataset_Emoji;
    Json::Value dataset_Emoji_favourite;

    Json::Value dataset_Slang_Word;
    Json::Value dataset_Slang_Word_favourite;

    Json::Value dataset_history;

public:
   Json::Value get_dataset(DictionaryId id);
    
public:
    static Database& get_instance() {
        static Database instance;
        return instance;
    }
    ~Database();

private:
    Database(); // Private constructor
    Database(const Database&) = delete; // Delete copy constructor
    Database& operator=(const Database&) = delete; // Delete copy assignment operator
};