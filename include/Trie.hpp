#pragma once

#include <PersistentTrie.hpp>
#include <string>
#include <map>

class Trie
{
private:
    friend class PersistentTrie;
    
    struct Node
    {
        static int id_counter;

        std::map<char, Node*> children;
        std::vector<std::string> definition;
        bool isWord;
        int id;

        Node();
        ~Node();
        Json::Value to_json();
    };
    Node* root;
    std::string version_description;
    void insert_helper(Node* node, const std::string &key, const std::string &definition);
    
public:
    Trie();
    ~Trie();
    void insert(const std::string &word, const std::string &definition);
    std::vector<std::string> search(const std::string &word);
    Json::Value to_json();
    std::vector<std::string> get_random_word_and_definition();
};
