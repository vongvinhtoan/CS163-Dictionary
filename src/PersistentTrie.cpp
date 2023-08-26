#include <PersistentTrie.hpp>
#include <Trie.hpp>
#include <vector>
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>

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
    if(dummy)
    {
        node->definition = dummy->definition;
        node->isWord = dummy->isWord;
    }

    std::cout<<"trie->root->id = "<<trie->root->id<<std::endl;
    for(char c: word) {
        node->children[c] = new Trie::Node();
        node = node->children[c];
        if(dummy && dummy->children.find(c) != dummy->children.end())
            dummy = dummy->children[c];
        else
            dummy = nullptr;

        if(dummy)
        {
            node->definition = dummy->definition;
            node->isWord = dummy->isWord;
        }
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
    if(dummy)
    {
        node->definition = dummy->definition;
        node->isWord = dummy->isWord;
    }

    static std::function<bool(Trie::Node*, Trie::Node*, const std::string &, int)> 
    DFS = [&](Trie::Node* node, Trie::Node* dummy, const std::string &word, int index) -> bool {
        if(index == word.size()) {
            bool isWord = node->isWord;
            node->isWord = false;
            node->definition.clear();
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
    if(dummy)
    {
        node->definition = dummy->definition;
        node->isWord = dummy->isWord;
    }

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
    std::cout<<"insert"<<std::endl;
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
    Json::Value root;
    root["firstroot"] = Json::Value();
    root["lastroot"] = Json::Value();
    root["nodes"] = Json::Value(Json::arrayValue);

    Trie* first = versions[0];
    Trie* last = versions.back();
    std::cout<<"version.size() = "<<versions.size()<<std::endl;
    std::cout<<"first = "<<first->root->id<<std::endl;
    std::cout<<"last = "<<last->root->id<<std::endl;

    root["firstroot"] = first->root->id;
    root["lastroot"] = last->root->id;

    int maxIndex = std::max(first->get_max_index(), last->get_max_index());

    std::vector<bool> visited(maxIndex + 1, false);

    std::queue<Trie::Node*> q;
    q.push(first->root);
    while(!q.empty())
    {
        Trie::Node* node = q.front();
        q.pop();
        visited[node->id] = true;
        Json::Value n = Json::Value();
        n["index"] = node->id;
        n["isWord"] = node->isWord;
        for(auto& child: node->children) {
            Json::Value child_node;
            child_node["index"] = child.second->id;
            child_node["key"] = child.first;
            n["children"].append(child_node);
        }
        for(auto& def: node->definition)
            n["definition"].append(def);
        for(auto& child: node->children)
        {
            if(!visited[child.second->id])
                q.push(child.second);
        }
        root["nodes"].append(n);
    }
    q.push(last->root);
    while(!q.empty())
    {
        Trie::Node* node = q.front();
        q.pop();
        if(visited[node->id]) continue;
        visited[node->id] = true;
        Json::Value n = Json::Value();
        n["index"] = node->id;
        n["isWord"] = node->isWord;
        for(auto& child: node->children) {
            Json::Value child_node;
            child_node["index"] = child.second->id;
            child_node["key"] = child.first;
            n["children"].append(child_node);
        }
        for(auto& def: node->definition)
            n["definition"].append(def);
        for(auto& child: node->children)
        {
            if(!visited[child.second->id])
                q.push(child.second);
        }
        root["nodes"].append(n);
    }

    return root;
}

void PersistentTrie::init_json(Json::Value root)
{
    std::cout<<"init_json\n";
    std::vector<Trie::Node*> nodes;
    std::vector<int> index_to_id;
    std::vector<int> id_to_index;
    std::vector<std::vector<std::pair<char, int>>> children;
    int maxIndex = 0;
    for(auto& node: root["nodes"]) {
        maxIndex = std::max(maxIndex, node["index"].asInt());
    }
    Trie::Node::id_counter = maxIndex + 1;
    id_to_index.resize(maxIndex + 1, -1);
    for(auto& node: root["nodes"]) {
        Trie::Node* n = new Trie::Node();

        n->id = node["index"].asInt();
        id_to_index[n->id] = nodes.size();
        index_to_id.push_back(n->id);

        for(auto& def: node["definition"])
            n->definition.push_back(def.asString());
            
        children.push_back(std::vector<std::pair<char, int>>());
        n->isWord = node["isWord"].asBool();
        for(auto& child: node["children"]) {
            children.back().push_back(std::make_pair(child["key"].asInt(), child["index"].asInt()));
        }

        nodes.push_back(n);
    }
    for(int i = 0; i < nodes.size(); i++) {
        for(auto& child: children[i]) {
            nodes[i]->children[child.first] = nodes[id_to_index[child.second]];
        }
        nodes[i]->id = id_to_index[nodes[i]->id];
    }

    Trie::Node* first = nodes[id_to_index[root["firstroot"].asInt()]];
    Trie::Node* last = nodes[id_to_index[root["lastroot"].asInt()]];

    Trie* trie = new Trie();
    delete trie->root;
    trie->root = first;
    versions.push_back(trie);

    trie = new Trie();
    delete trie->root;
    trie->root = last;
    versions.push_back(trie);

    std::cout<<first->id<<" "<<last->id<<std::endl;
}

void PersistentTrie::clone()
{
    versions.push_back(versions.back());
}
std::vector<std::string> PersistentTrie::dfs()
{
    return versions.back()->dfs();
}

void PersistentTrie:: initialize_again(std::string s){
    std::cout<<"initialize_again\n";
    Trie* trie = new Trie();
    
        trie->deserialize(s);

    trie->version_description = "Version 0: initialize \n";
    versions.push_back(trie);
}
