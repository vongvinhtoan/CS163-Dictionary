#pragma once

#include <vector>
#include <string>

class Trie;

class PersistentTrie
{
private:
    std::vector<Trie*> children;
    Trie* insert(const std::string &word, const std::string &definition, int index);

public:
    PersistentTrie();
    ~PersistentTrie();
    Trie* getChild(int index);
    void insert(const std::string &key, const std::string &definition);
};
