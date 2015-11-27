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
    void put(const Key &key, Item value);
    Item get(const Key &key);
    void remove(const Key &key);

    /// Describe current state of the tree
    bool contains(const Key &key);
    int size();
    bool isEmpty();

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

};

#endif // BST_H
