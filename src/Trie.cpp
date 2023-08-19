#include <Trie.hpp>
#include <json.h>
#include <queue>
#include <iostream>
#include<time.h>
int Trie::Node::id_counter = 0;

Trie::Node::Node()
: children()
, isWord(false)
, definition()
, id(id_counter++)
{
    std::cout<<"Node "<<id<<" created\n";
}

Trie::Node::~Node()
{
    for(auto& child: children)
        delete child.second;
}

Trie::Trie()
: root(new Node())
{
}

Trie::~Trie()
{
    delete root;
}

void Trie::insert_helper(Node* node, const std::string &key, const std::string &definition)
{
    for(auto c: key)
    {
        if(node->children.find(c) == node->children.end())
            node->children[c] = new Node();
        node = node->children[c];
    }
    node->isWord = true;
    node->definition.push_back(definition);
}

void Trie::insert(const std::string &key, const std::string &definition)
{
    insert_helper(root, key, definition);
}

std::vector<std::string> Trie::search(const std::string &key)
{
    Node* node = root;
    for(auto c: key)
    {
        if(node->children.find(c) == node->children.end())
            return std::vector<std::string>();
        node = node->children[c];
    }
    return node->definition;
}

Json::Value Trie::Node::to_json()
{
    Json::Value node;
    node["id"] = id;
    node["isWord"] = isWord;
    for(auto& child: children) {
        Json::Value child_node;
        child_node["id"] = child.second->id;
        child_node["char"] = child.first;
        node["children"].append(child_node);
    }

    for(auto& def: definition)
        node["definition"].append(def);
    return node;
}

Json::Value Trie::to_json()
{
    Json::Value trie;
    trie["root"] = root->id;
    trie["nodes"] = Json::Value(Json::arrayValue);
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        Node* node = q.front();
        trie["nodes"].append(node->to_json());
        q.pop();
        for(auto& child: node->children)
        {
            q.push(child.second);
        }
    }
    return trie;
}

std::vector<std::string> Trie:: get_random_word(){
    Node* node=root;
    std::vector<std::string> word_and_definition;
    std::string word;
   
    int y=rand()%(10+1);
    
    for(int i=0;i<y;i++){
        if(node->children.empty()){
            word_and_definition=node->definition;
            word_and_definition.push_back(word);   
            return word_and_definition;
        }
        std::map<char, Node*>::iterator it =node->children.begin();
        std::advance(it, rand() % (node->children.size()));
        word.push_back(it->first);
        node=it->second;
    }

    if(node->isWord){
        
        word_and_definition= node->definition;
        word_and_definition.push_back(word);
        return word_and_definition;
    }

    else{
        while(!node->isWord){
        std::map<char, Node*>::iterator it =node->children.begin();
        std::advance(it, rand() % (node->children.size()));
        word.push_back(it->first);
        node=it->second;     
        }
        word_and_definition=node->definition;
        word_and_definition.push_back(word);
        return word_and_definition;
    }
    return word_and_definition;
}