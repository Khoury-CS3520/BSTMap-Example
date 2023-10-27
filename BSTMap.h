//
// Created by MARK FONTENOT on 10/26/23.
//
// This is not a fully fleshed out Map Class and is used for
// demo purposes only.

#ifndef BSTREE_BSTMAP_H
#define BSTREE_BSTMAP_H

#include <stdexcept>
#include <iostream>

template <typename Key, typename Value>
class BSTMap {
private:
    class BSTNode {
    public:
        Key key;
        Value value;
        BSTNode* left;
        BSTNode* right;

        BSTNode(const Key& k, const Value& v);
    };

    BSTNode* root{nullptr};

    //Private Helper Functions to suppor recursive ops
    void insert(BSTNode*& node, const Key& key, const Value& value);
    BSTNode* search(BSTNode* curr, const Key& searchKey);
    void clearMap(BSTNode* curr);
    BSTNode* copyMap(BSTNode* curr);

    //used for demo purposes
    void traverse(BSTNode* curr) {
        if (curr) {
            traverse(curr->left);
            std::cout << curr->key << " : " << curr->value << std::endl;
            traverse(curr->right);
        }
    }

public:
    BSTMap() = default;
    ~BSTMap();
    BSTMap(const BSTMap& other);
    BSTMap& operator=(const BSTMap& other);

    void insert(const Key& key, const Value& value);
    Value& search(const Key& searchKey);

    //TODO: delete node

    void traverse() {traverse(root);}
};

////////////////////////////////////////////
//-------------- BSTNode --------------
////////////////////////////////////////////


template <typename Key, typename Value>
BSTMap<Key, Value>::BSTNode::BSTNode(const Key& k, const Value& v)
        : key(k), value(v), left(nullptr), right(nullptr) {}

////////////////////////////////////////////
//-------------- BSTMap --------------
////////////////////////////////////////////

//   COPY Constructor
template<typename Key, typename Value>
BSTMap<Key, Value>::BSTMap(const BSTMap& arg) {
    root = copyMap(arg.root);
}

//   Operator= COPY Assignment
template<typename Key, typename Value>
BSTMap<Key, Value>& BSTMap<Key, Value>::operator=(const BSTMap& arg) {
    if(this != &arg) {
        clearMap(root);
        root = copyMap(arg.root);
    }
    return *this;
}

////////////////////////////////////////////
//   DELETE / Clear the Tree
////////////////////////////////////////////

template<typename Key, typename Value>
void BSTMap<Key, Value>::clearMap(BSTNode* curr) {
    if(curr != nullptr) {
        clearMap(curr->left);
        clearMap(curr->right);
        delete curr;
    }
}
////////////////////////////////////////////
//   DESTRUCTOR
////////////////////////////////////////////

template<typename Key, typename Value>
BSTMap<Key, Value>::~BSTMap() {
    clearMap(root);
}

////////////////////////////////////////////
//   INSERT Functionality
////////////////////////////////////////////

//public interface insert
template <typename Key, typename Value>
void BSTMap<Key, Value>::insert(const Key& key, const Value& value) {
    insert(root, key, value);
}

//private recursive helper insert
template <typename Key, typename Value>
void BSTMap<Key, Value>::insert(BSTNode*& node,
                                const Key& key,
                                const Value& value) {
    if (node == nullptr) {
        node = new BSTNode(key, value);
    }
    if (key < node->key) {
        insert(node->left, key, value);
    } else if (key > node->key) {
        insert(node->right, key, value);
    } else {
        //if the node already exists, this will update the old
        //value with the new one
        node->value = value;
    }
}
////////////////////////////////////////////
//    SEARCH Functionality
////////////////////////////////////////////

//public interface search
template <typename Key, typename Value>
Value& BSTMap<Key, Value>::search(const Key& searchKey) {
    return search(root, searchKey)->value;
}

//private recursive search
//Note that it returns a pointer to a node in the tree
//and the fact that you need to use typename to declare the
//return type
template <typename Key, typename Value>
typename BSTMap<Key, Value>::BSTNode* BSTMap<Key, Value>::search(BSTNode* curr,
                                                                 const Key& searchKey) {
    if(curr == nullptr || curr->key == searchKey) {
        return curr;
    }
    if (searchKey < curr->key) {
        return search(curr->left, searchKey);
    }
    return search(curr->right, searchKey);
}

////////////////////////////////////////////
//   COPY Functionality
////////////////////////////////////////////

template<typename Key, typename Value>
typename BSTMap<Key, Value>::BSTNode* BSTMap<Key, Value>::copyMap(BSTNode* curr) {
    if(curr == nullptr) {
        return nullptr;
    }
    BSTNode* newNode = new BSTNode(curr->key, curr->value);
    newNode->left = copyMap(curr->left);
    newNode->right = copyMap(curr->right);
    return newNode;
}

#endif //BSTREE_BSTMAP_H


