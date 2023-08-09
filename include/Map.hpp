#pragma once

#include <utility>
#include <optional>

template <typename KeyType, typename ValueType>
class Map
{
private:
    struct Node
    {
        KeyType key;
        ValueType value;
        int height;
        Node* left;
        Node* right;

        Node(KeyType key = KeyType(), ValueType value = ValueType());
        ~Node();
    };

    Node* root;
    void insert(Node*& node, KeyType key, ValueType value);
    Node* find(Node* node, KeyType key);
    void erase(Node*& node, KeyType key);

public:
    Map();
    ~Map();
    void insert(KeyType key, ValueType value);
    void erase(KeyType key);
    ValueType& operator[](KeyType key);
    std::optional<std::pair<KeyType, ValueType>> find(KeyType key);
};

#include "Map.inl"