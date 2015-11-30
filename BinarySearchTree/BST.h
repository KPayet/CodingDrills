#ifndef BST_H
#define BST_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// BST.H
//  This file declares a template class for a key-value data structure based on BST
//  The current implementation is an associative array, i.e. it doesn't allow duplicate keys
//  However, values associated with the keys can be updated
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <memory>
#include <iostream>

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
        return &(x->value);
    }
    /// This function removes a key from the tree,
    /// and recursively update the tree structure
    void remove(const Key &key) {
        root = remove(root, key);
    }

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

        const Key key;
        Item value;
        NodePtr left, right;

        Node(const Key &k, Item v): key(k), value(v) {
            // no need to initialize left and right to null, shared_ptr does it for us.
        }
    };

    /// helper functions for put and get implementations
    NodePtr put(NodePtr x, const Key &key, Item value);
    NodePtr get(NodePtr x, const Key &key);

    /// helpers for remove key
    NodePtr remove(NodePtr node, const Key &key);
    // returns Node with minimum key in subtree with root x
    NodePtr min(NodePtr x) {
        if (!x->left) return x;
        else return min(x->left);
    }
    NodePtr deleteMin(NodePtr x) {
        if (!x->left) return x->right;
        x->left = deleteMin(x->left);

        return x;
    }

};


/// recursive implementation of put function
template <typename Key, typename Item>
typename BST<Key, Item>::NodePtr BST<Key, Item>::put(NodePtr node, const Key &key, Item value) {

    /// if we reach nullptr, it means that the key doesn't exist in the tree
    /// So, we create a new Node, update Node number, and return
    if(!node) { ++N; return std::shared_ptr<Node>(new Node(key, value)); }

    /// if input key is smaller than current key, add (key, value) pair in left subtree
    /// if it is greater, in right subtree. If it is equal, then the key already exists, and we simply update the value
    if(key < node->key) node->left = put(node->left, key, value);
    else if(key > node->key) node->right = put(node->right, key, value);
    else node->value = value;

    return node;
}

/// recursively look for Node with a given key in the tree, and return a pointer to said Node when found
template <typename Key, typename Item>
typename BST<Key, Item>::NodePtr BST<Key, Item>::get(NodePtr node, const Key &key) {

    // if we reach a leaf, it means the key has not been found. So we return null
    if(!node) return nullptr;

    //
    if(key < node->key) return get(node->left, key);
    else if(key > node->key) return get(node->right, key);
    else return node;
}

/// delete Node from tree.
/// We use Hibbard deletion scheme, in which there are 4 cases to consider:
///     1 - Node doesn't exist, do nothing
///     2 - Node is a leaf. Simply remove the Node
///     3 - Node has exactly one child. In this case, we simply bypass the Node, like in a linked list
///     4 - Node has 2 children. In this case, we swap the Node with the smallest Node in its right subtree
///         And delete the Node that is now a leaf
///
///     Note: This deletion strategy is known for unbalancing BSTs after many delete
///           i.e. this data structure is not the best way to implement an efficient associative array
///
template <typename Key, typename Item>
typename BST<Key, Item>::NodePtr BST<Key, Item>::remove(NodePtr node, const Key &k) {
    // limit condition. Means that we didn't find a Node with key k. So do nothing Case #1
    if(!node) return nullptr;

    // first we recursively search for the Node with key k
    if(key < node->key) node->left  = remove(node->left,  key);
    else if(key > node->key) node->right = remove(node->right, key);
    else {  // Node with key k found!
        if(!node->right) return node->left;
        if(!node->left) return node->right;
        std::cout<<"Two children!"<<std::endl;
        NodePtr x = node;
        node = min(x->right);   // swap node with smallest Node in its right subtree
        node->right = deleteMin(x->right);
        node->left = x->left;
    }

    return node;
}

#endif // BST_H
