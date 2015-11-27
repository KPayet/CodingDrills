#ifndef BST_H
#define BST_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// BST.H
//  This file declares a template class for a key-value data structure based on BST
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <memory>

template <class Key, class Item>
class BST {
    class Node;
    typedef std::shared_ptr<Node> NodePtr;

public:
    BST():N(0) {}

    /// Insert, retrieve, delete key-value pairs
    void put(const Key &key, Item value) {
        /// insert new node, and update the tree structure recursively
        root = put(root, key, value);
    }
    /// I decided to make get return a reference to the value,
    /// so that user can do test like: if(!get(someKey)) { ... }
    /// Otherwise I don't really know how to deal with the case when the key is not present in the tree
    Item *get(const Key &key) {
        NodePtr x = get(root, key);
        if(!x) return nullptr;
        return x->value;
    }
    void remove(const Key &key);

    /// Describe current state of the tree
    bool contains(const Key &key){
        if(!get(key)) return false;
        return true;
    }
    int size() {return N;}
    bool isEmpty() {return N == 0;}

    /// return all keys. Implement inorder DFS, BFS, ... ?


private:
    /// a BST is defined merely by a reference to the root Node
    int N;  // number of nodes
    NodePtr root;

    class Node{
        friend class BST<Key, Item>;

        Key key;
        Item value;
        NodePtr left, right;

        Node(const Key &key, Item value) {
            this->key = key;
            this->value = value;
            // no need to initialize left and right to null, shared_ptr does it for us.
        }
    };

    /// helper functions for put and get implementations
    NodePtr put(NodePtr x, const Key &key, Item value);
    NodePtr get(NodePtr x, const Key &key);

};

template <typename Key, typename Item>
typename BST<Key, Item>::NodePtr BST<Key, Item>::put(NodePtr x, const Key &key, Item value) {
    if(!x) return std::shared_ptr<Node>(new Node(key, value));
}

template <typename Key, typename Item>
typename BST<Key, Item>::NodePtr BST<Key, Item>::get(NodePtr x, const Key &key) {}

#endif // BST_H
