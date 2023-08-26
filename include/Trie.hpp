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

        Node(int id = id_counter++);
        ~Node();
        Json::Value to_json();
    };
    Node* root;
    std::string version_description;
    void insert_helper(Node* node, const std::string &key, const std::string &definition);
    std::vector<std::string> dfs_helper( Node* node,std::vector<std::string> data,std::string word);
    std::string serialize_helper(Node* node);
    void deserialize_helper(Node* node,std::string str,int& i);
public:
    Trie();
    ~Trie();
    void insert(const std::string &word, const std::string &definition);
    std::vector<std::string> search(const std::string &word);
    Json::Value to_json();
    std::vector<std::string> get_random_word();
    std::vector<std::string>dfs();
    bool check_exist(const std::string &word);
    std::string serialize();
    void deserialize(std::string str);
    int get_max_index();
};
