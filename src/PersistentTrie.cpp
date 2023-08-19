#include <PersistentTrie.hpp>
#include <Trie.hpp>
#include <vector>
#include <cassert>
#include <functional>
#include <iostream>

PersistentTrie::PersistentTrie()
{
}

PersistentTrie::~PersistentTrie()
{
    for(auto& version: versions)
        delete version;
}

Trie* PersistentTrie::get_version(int version_id)
{    
    return versions[version_id];
}

Trie* PersistentTrie::insert_helper(const std::string &word, const std::string &definition)
{
    assert(versions.size() > 0);

    Trie* trie = new Trie();
    trie->version_description  = "Version " + std::to_string(versions.size()) + ": insert \n";
    trie->version_description += "Word: " + word + "\n";
    trie->version_description += "Definition: " + definition + "\n";
    Trie* old = versions.back();

    Trie::Node* node = trie->root;
    Trie::Node* dummy = old->root;
    if(dummy) (*node) = (*dummy);

    for(char c: word) {
        node->children[c] = new Trie::Node();
        node = node->children[c];
        if(dummy && dummy->children.find(c) != dummy->children.end())
            dummy = dummy->children[c];
        else
            dummy = nullptr;

        if(dummy) (*node) = (*dummy);
    }

    node->isWord = true;
    node->definition.push_back(definition);

    return trie;
}

Trie* PersistentTrie::delete_word_helper(const std::string &word)
{
    assert(versions.size() > 0);

    Trie* trie = new Trie();
    trie->version_description  = "Version " + std::to_string(versions.size()) + ": delete word \n";
    trie->version_description += "Word: " + word + "\n";
    Trie* old = versions.back();

    Trie::Node* node = trie->root;
    Trie::Node* dummy = old->root;
    if(dummy) (*node) = (*dummy);  

    static std::function<bool(Trie::Node*, Trie::Node*, const std::string &, int)> 
    DFS = [&](Trie::Node* node, Trie::Node* dummy, const std::string &word, int index) -> bool {
        if(index == word.size()) {
            bool isWord = node->isWord;
            node->isWord = false;
            return isWord;
        }

        Trie::Node* new_node = new Trie::Node();
        Trie::Node* new_dummy = nullptr;
        if(dummy && dummy->children.find(word[index]) != dummy->children.end())
            new_dummy = dummy->children[word[index]];

        if(new_dummy) (*new_node) = (*new_dummy);
        node->children[word[index]] = new_node;

        if(DFS(new_node, new_dummy, word, index + 1)) {
            if(new_node->children.size() == 0 && !new_node->isWord) {
                delete new_node;
                node->children.erase(word[index]);
            }
            return true;
        }

        return false;
    };

    if(!DFS(node, dummy, word, 0)) {
        delete trie;
        trie = nullptr;
    }

    return trie;
}

Trie* PersistentTrie::delete_definition_helper(const std::string &word, const std::string &definition)
{
    assert(versions.size() > 0);

    Trie* trie = new Trie();
    trie->version_description  = "Version " + std::to_string(versions.size()) + ": delete definition \n";
    trie->version_description += "Word: " + word + "\n";
    trie->version_description += "Definition: " + definition + "\n";
    Trie* old = versions.back();

    Trie::Node* node = trie->root;
    Trie::Node* dummy = old->root;
    if(dummy) (*node) = (*dummy);

    static std::function<bool(Trie::Node*, Trie::Node*, const std::string&, const std::string&, int)> 
    DFS = [&](Trie::Node* node, Trie::Node* dummy, const std::string &word, const std::string &definition, int index) -> bool {
        if(index == word.size()) {
            for(int i = 0; i < node->definition.size(); i++) {
                if(node->definition[i] == definition) {
                    node->definition.erase(node->definition.begin() + i);
                    return true;
                }
            }
            return false;
        }

        Trie::Node* new_node = new Trie::Node();
        Trie::Node* new_dummy = nullptr;
        if(dummy && dummy->children.find(word[index]) != dummy->children.end())
            new_dummy = dummy->children[word[index]];

        if(new_dummy) (*new_node) = (*new_dummy);
        node->children[word[index]] = new_node;

        if(DFS(new_node, new_dummy, word, definition, index + 1)) {
            if(new_node->children.size() == 0 && new_node->definition.size() == 0) {
                delete new_node;
                node->children.erase(word[index]);
            }
            return true;
        }

        return false;
    };

    if(!DFS(node, dummy, word, definition, 0)) {
        delete trie;
        trie = nullptr;
    }

    return trie;
}

void PersistentTrie::insert(const std::string &word, const std::string &definition)
{
    versions.push_back(insert_helper(word, definition));
}

bool PersistentTrie::delete_word(const std::string &word)
{
    Trie* trie = delete_word_helper(word);
    if(trie == nullptr)
        return false;
    versions.push_back(trie);
    std::cout<<"version.push_back(trie); + delete_word\n";
    return true;
}

bool PersistentTrie::delete_definition(const std::string &word, const std::string &definition)
{
    Trie* trie = delete_definition_helper(word, definition);
    if(trie == nullptr)
        return false;
    versions.push_back(trie);
    std::cout<<"version.push_back(trie); + delete_definition\n";
    return true;
}

void PersistentTrie::initialize(std::vector<std::pair<std::string, std::string>> &words)
{
    Trie* trie = new Trie();
    for(auto &word: words)
        trie->insert(word.first, word.second);

    trie->version_description = "Version 0: initialize \n";
    versions.push_back(trie);
    //std::cout<<"version.push_back(trie); + initialize\n";
}

Json::Value PersistentTrie::to_json()
{
    Json::Value root = Json::Value(Json::arrayValue);
    //std::cout<<versions.size()<<std::endl;
    for(int i = 0; i < versions.size(); i++) {
        Json::Value version;
        version["version"] = i;
        version["trie"] = versions[i]->to_json();
        version["description"] = versions[i]->version_description;
        root.append(version);
    }
    return root;
}