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
        std::map<char, Node*> children;
        bool isWord;
        std::string definition;
        Node* root;

        Node();
        Node(Node* root);
        ~Node();
    };

    Node* root;
    std::string find(Node* node, const std::string &key);

public:
    Trie();
    ~Trie();
    std::string find(const std::string &key);
};
