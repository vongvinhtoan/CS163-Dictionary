#pragma once

#include <vector>
#include <string>
#include <json.h>

class Trie;

class PersistentTrie
{
private:
    std::vector<Trie*> versions;
    Trie* insert_helper(const std::string &word, const std::string &definition);
    Trie* delete_word_helper(const std::string &word);
    Trie* delete_definition_helper(const std::string &word, const std::string &definition);
    Trie* edit_definition_helper(const std::string &word, int editID, const std::string &definition);
    
public:
    PersistentTrie();
    ~PersistentTrie();
    Trie* get_version(int version_id);
    void insert(const std::string &word, const std::string &definition);
    bool delete_word(const std::string &word);
    bool delete_definition(const std::string &word, const std::string &definition);
    void initialize(std::vector<std::pair<std::string, std::string>> &words);
    void init_json(Json::Value root);
    void clone();
    Json::Value to_json();
    std::vector<std::string> dfs();
    void edit_definition(std::string word, int editID, std::string definition);
};


