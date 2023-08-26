#include <Trie.hpp>
#include <json.h>
#include <queue>
#include <iostream>
#include<time.h>
int Trie::Node::id_counter = 0;

Trie::Node::Node(int id)
: children()
, isWord(false)
, definition()
, id(id)
{
    
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
    if(!node->isWord) return std::vector<std::string>();
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
std::vector<std::string> Trie::dfs(){
   Node* node=root;
   std::vector<std::string> data;
   std::string word;
   return dfs_helper(node,data,word); 
}
std::vector<std::string> Trie:: dfs_helper(Node* node,std::vector<std::string> data,std::string word){
    if(node->isWord){
        data.push_back(word);
    }
    for(auto& child: node->children){
        dfs_helper(child.second,data,word+child.first);
    }
    return data;
}
bool Trie::check_exist(const std::string &key){
    Node* node = root;
    
    for(auto c: key)
    {
        if(node->children.find(c) == node->children.end())
            return false;
        node = node->children[c]; 
    }
    return true;
}

std::string Trie::serialize_helper(Node* node){
    std::string data;
    if(node->isWord){

        data+=char(1);
        for(int i=0;i<node->definition.size();i++){
            data+=char(2);
            data+=node->definition[i];
            
        }
        data+=char(3);
    }
    else{
        data+=char(0);
    }
    for(auto& child: node->children){
        data+=child.first;
        data+=serialize_helper(child.second);

    }
    data+=char(4);
    return data;
}

std::string Trie::serialize(){
    Node* node=root;
    std::string data;
    data+=serialize_helper(node);
    return data;
}

void Trie::deserialize(std::string str)
{
    int i=0;
    deserialize_helper(root,str,i);
   
    return; 
}
void Trie::deserialize_helper(Node* node,std::string str,int& i){
    while(i<str.size()){
        if(str[i]==char(0)){
            //std::cout<<i<<" NOT IS WORD\n";
            node->isWord=false;
            i++;
            //std::cout<<i<<"\n";
           
            continue;
        }
        else if(str[i]==char(1)){
            // std::cout<<i;
            // std::cout<<" IS WORD\n";
            node->isWord=true;
            i++;
           
            while(str[i]!=char(3)){
                if(str[i]==char(2)){
                    i++;
                    std::string definition;
                    while(str[i]!=char(2)&&str[i]!=char(3)){
                        definition+=str[i];
                        i++;
                    }
                    
                    node->definition.push_back(definition);
                    //std::cout<<definition<<"\n";
                }
            }
            i++;
            continue;
        }

        else if(str[i]==char(4)){
            //std::cout<<i<<" END OF LIST\n";
            i++;
            
            return;
        }
                 
        else  {
            //std::cout<<i<<"concutobu "<<str[i] <<"\n";
            node->children[str[i]]=new Node();
            int temp=i;
            i++;
            
            deserialize_helper(node->children[str[temp]],str,i);
            
        }

    }

}

int Trie::get_max_index(){
    Node* node=root;
    int max=0;
    std::queue<Node*> q;
    q.push(node);
    while(!q.empty()){
        Node* node=q.front();
        q.pop();
        if(node->id>max){
            max=node->id;
        }
        for(auto& child: node->children){
            q.push(child.second);
        }
    }
    return max;
}
 std::string Trie::get_version_description(){
     return version_description;
 }

//use ACSII char to represent the tree
//0: not a word
//1: is a word
//2: start of definition
//3: end of definition
//4: end of word