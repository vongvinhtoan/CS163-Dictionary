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

Trie::Trie()
: root(new Node())
{
}

Trie::~Trie()
{
    delete root;
}

std::string Trie::find(Node* node, const std::string &key)
{
    // Code here
}

std::string Trie::find(const std::string &key)
{
    return find(root, key);
}