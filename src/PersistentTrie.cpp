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
bool PersistentTrie::check(const std::string &word, const std::string &definition, int index)
{
    // Code here
    Trie::Node* node=children[index]->root;
   for(auto c: word)
    {
        if(node->children.find(c) == node->children.end())
            return false;
        node = node->children[c];
    }
    if(node->isWord==true)        return false;
    for(int i=0;i<node->definition.size();i++)
    {
        if(node->definition[i].compare(definition))
            return false;
    }
    return true;
}
Trie* PersistentTrie::insert(const std::string &word, const std::string &definition, int index)
{
    if(check(word, definition, index)==true)
        return children[index];
    // Code here
    Trie* new_trie;
    children.push_back(new_trie);

    Trie::Node* node=new_trie->root;
    
     Trie::Node* dummy=children[index]->root;   
     for(int i=0;i<word.size();i++){
        for(auto x:dummy->children){
            if(word[i]!='x.first')node->children[x.first]=x.second;  
            else{
                node->children[word[i]]=new Trie::Node();
                node= node->children[word[i]];
            }
        }         
    }
    node->isWord=true;
    node->definition.push_back(definition);
    return new_trie;
}
void PersistentTrie::insert(const std::string &key, const std::string &definition){
    
    children.push_back(insert(key, definition, children.size()));
}