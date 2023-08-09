#include <iostream>
#include <cassert>

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Node::Node(KeyType key, ValueType value)
    : key(key)
    , value(value)
    , height(0)
    , left(nullptr)
    , right(nullptr)
{
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Node::~Node()
{
    delete left;
    delete right;
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map()
    : root(nullptr)
{
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::~Map()
{
    delete root;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(KeyType key, ValueType value)
{
    insert(root, key, value);
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(Node*& node, KeyType key, ValueType value)
{
    // Code here
}

template <typename KeyType, typename ValueType>
ValueType& Map<KeyType, ValueType>::operator[](KeyType key)
{
    Node* result = find(root, key);
    if (!result || result->key != key) insert(key, ValueType());
    return find(root, key)->value;
}

template <typename KeyType, typename ValueType>
std::optional<std::pair<KeyType, ValueType>> Map<KeyType, ValueType>::find(KeyType key)
{
    Node* result = find(root, key);
    if (!result || result->key != key) return std::nullopt;
    return std::make_pair(result->key, result->value);
}

template <typename KeyType, typename ValueType>
typename Map<KeyType, ValueType>::Node* Map<KeyType, ValueType>::find(Node* node, KeyType key)
{
    // Code here
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::erase(KeyType key)
{
    erase(root, key);
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::erase(Node*& node, KeyType key)
{
    // Code here
}