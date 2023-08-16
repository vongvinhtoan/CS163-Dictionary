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

std::vector<std::string> Trie:: get_random_word_and_definition(){
    Node* node=root;
    std::vector<std::string> word_and_definition;
    std::string word;
    srand((int)time(0));
    int y=rand()%(10+1);
    
    for(int i=0;i<y;i++){
        int n=rand()%(26+1);
        std::cout<<n<<std::endl;
        char find_char = 'a' + n;
        if(!node->children.empty()){
            while(node->children.find(find_char) == node->children.end()){
                
                n=rand()%(26+1);
                std::cout<<n<<std::endl;
                find_char = 'a' + n;
            }

            word.push_back(find_char);
            node = node->children[find_char];
        }

        else {
            word_and_definition=node->definition;
            word_and_definition.push_back(word);   
            return word_and_definition;
        }

    }

    if(node->isWord){
        
        word_and_definition= node->definition;
        word_and_definition.push_back(word);
        return word_and_definition;
    }

    else{
        while(!node->isWord){
            int n=rand()%(26+1);
            char find_char = 'a' + n;
                while(node->children.find(find_char) == node->children.end()){
                n=rand()%(26+1);
                find_char = 'a' + n;
            }
            node = node->children[find_char];
            word.push_back(find_char);

            
           
        }
        word_and_definition=node->definition;
        word_and_definition.push_back(word);
        return word_and_definition;
    }
    return word_and_definition;
        

}



// std::string Trie::find(Node* node, const std::string &key)
// {
//     // Code here
//     for(auto c: key) {
//         if(node->children.find(c) == node->children.end())
//             return "Word not found";
//         node = node->children[c];
//     }

//     if(!node->isWord)
//         return "No definition found";
    
//     std::string s;
//     for(auto c: node->definition)
//         s+= c;
//     return s;
// }

// std::string Trie::find(const std::string &key)
// {
//     return find(root, key);
// }
// void Trie::insert(Node* node, const std::string &key, const std::string &definition)
// {
//     for(auto c: key)
//     {
//         if(node->children.find(c) == node->children.end())
//         node->children[c] = new Node();
//         node = node->children[c];
//     }
//     node->isWord = true;
//     node->definition.push_back(definition);

// }
// void Trie::insert(const std::string &key, const std::string &definition)
// {
//     insert(root, key, definition);
// }

