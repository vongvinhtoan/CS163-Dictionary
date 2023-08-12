#include <Trie.hpp>

Trie::Node::Node()
: children()
, isWord(false)
, definition()
, root(this)
{
}

Trie::Node::Node(Node* root)
: children()
, isWord(false)
, definition()
, root(root)
{
}

Trie::Node::~Node()
{
    // Didn't have .begin() and .end() and iterator, wait for the code
    // for(auto& child: children)
    //     delete child.second;
}

Trie::Trie(): root(new Node())
{
    
}

Trie::~Trie()
{
    delete root;
}

std::string Trie::find(Node* node, const std::string &key)
{
    // Code here
    for(auto c: key)
    {
        if(node->children.find(c) == node->children.end())
            return "Word not found";
        node = node->children[c];
    }
    if(node->isWord==false)
        return "No definition found";
        std::string s;
    for(auto c: node->definition)
        s+= c;
        return s;
}

std::string Trie::find(const std::string &key)
{
    return find(root, key);
}
void Trie::insert(Node* node, const std::string &key, const std::string &definition)
{

    // Code here
    for(auto c: key)
    {
        if(node->children.find(c) == node->children.end())
        node->children[c] = new Node(node->root);
        node = node->children[c];
    }
    node->isWord = true;
    node->definition.push_back(definition);

}
void Trie::insert(const std::string &key, const std::string &definition)
{
    insert(root, key, definition);
}

