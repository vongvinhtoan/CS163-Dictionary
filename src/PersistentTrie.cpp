#include <PersistentTrie.hpp>
#include <Trie.hpp>
#include<vector>
using namespace std;
PersistentTrie::PersistentTrie()
{
}

PersistentTrie::~PersistentTrie()
{
    for(auto& child: children)
        delete child;
}

Trie* PersistentTrie::getChild(int index){
    
    return children[index];
}

Trie* PersistentTrie::insert(const std::string &word, const std::string &definition, int index)
{
    // Code here
    for(auto f:word){
        int c=f-'a';
        if(children[index]->root->children[c]==nullptr){
            children.push_back(new Trie());
            children[index]->root->children[c]=children.back()->root;
        }
        children[index]->root=children[index]->root->children[c];
    }  
        children.push_back(new Trie());
        children[index]->root->isWord=true;
        children[index]->root->definition=definition;
        return children[index];
}

void PersistentTrie::insert(const std::string &key, const std::string &definition){
    
    children.push_back(insert(key, definition, children.size()));
}