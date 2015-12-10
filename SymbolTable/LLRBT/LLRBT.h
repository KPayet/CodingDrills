#ifndef LLRBT_H
#define LLRBT_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// LLRBT.H
//  This file declares a template class that describes a key-value pair data structure based on LLRB-BST
//  Left-Leaning Red-Black Binary Search Tree
//  The implementation is pretty close to that of BST.h, but it also introduces the concept of color
//  that allows to balance the Binary Search Tree, i.e. keep its maximum height to a minimum value (logN).
//  Since, in a BST, complexity is dictated by the maximum depth (height of tree), such structure allows to guarantee O(logN) performance.
//  In fact, LLRB-BST data structure (as implemented here) emulates a 2-3 tree (see https://en.wikipedia.org/wiki/2%E2%80%933_tree).
//  2-3 tree are self-balancing trees that are perfect to implement ordered symbol tables with high performances (low complexity).
//  But the implementation can be a little tricky.
//  LLRB-BST solves this problem by representing 3-nodes (see wikipedia description) by simple nodes connected through a RED edge.
//  BLACK edges are standard edges that connect parent Node to children Nodes.
//  The important properties of a LLRB-BST:
//
//
//  It supports basic operations: put, get, remove, contains, isEmpty
//  + ordered operations getMin and getMax (return Item data associated with min/max key)
//  Other operations such as floor, ceiling, rank ... can be implemented too, but I didn't do it for now,
//  because my goal was more the core associative array structure
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <memory>
#include <vector>
#include <type_traits>

#include <iostream>

template <typename Key, typename Item>
class LLRBT {

    class Node;
    typedef std::shared_ptr<Node> NodePtr;  // used for clarity + ease of memory management

///
///     Public API
/// The API is strictly the same as the BST one
///
public:

    LLRBT():N(0) {}   // the root NodePtr is set to nullptr automatically

    ///
    /// Insert, retrieve, delete key-value pairs
    ///

    void put(const Key &key, Item value) { //   insert
        /// insert new node, and update the tree structure recursively
        root = put(root, key, value);   //  defined in private methods
        root->color = Color::BLACK;     // in case of flipColors, root might now be RED
    }

    /// I decided to make get return by address,
    /// so that user can do test like: if(!get(someKey)) { ... }
    /// Otherwise I don't really know how to deal with the case when the key is not present in the tree
    Item *get(const Key &key) { //  retrieve
        NodePtr x = get(root, key); //  defined in private methods
        if(!x) return nullptr;
        return &(x->value); //  I don't find this really elegant, but I can't think of another way right now
    }

    /// This function removes a key from the tree,
    /// and recursively update the tree structure
    void remove(const Key &key) {   //  delete

        if(!contains(key))  return;

        if (!isRed(root->left) && !isRed(root->right))
            root->color = Color::RED;                   // this is only temporary. We will make the root BLACK again below

        root = remove(root, key);   //  defined in private methods

        if (!isEmpty()) root->color = Color::BLACK;     // see ?
    }

    ///
    /// Describe current state of the tree
    ///

    bool contains(const Key &key){
        if(!get(key)) return false;
        return true;
    }

    int size() {return N;}

    bool isEmpty() {return N == 0;}

    /// return a pointer to the data associated with the min and max keys in the tree
    Item *getMin() {
        NodePtr x = min(root);
        if(!x) return nullptr;
        return &(x->value);
    }

    Item *getMax() {
        NodePtr x = max(root);
        if(!x) return nullptr;
        return &(x->value);
    }

    /// return all keys in order. I chose to use a vector<Key> to store the keys
    /// Could have been a queue<Key>. But in both cases, you can use for(auto k: *(tree->keys()) ) { ... }
    /// and the vector allows to access 2nd smallest, 3rd smallest, ..., keys
    ///
    /// auto v = *(tree->keys()); // and v is your Keys vector

    std::shared_ptr<std::vector<Key>> keys() {

        std::shared_ptr<std::vector<Key>> v(new std::vector<Key>());
        inorder<false>(root, v);    //  collects keys or items in order. See definition below

        return v;
    }

    /// return all items in order (in Keys order)
    std::shared_ptr<std::vector<Item>> items() {

        std::shared_ptr<std::vector<Item>> v(new std::vector<Item>());
        inorder<true>(root, v); // collects keys or items in order. See definition below

        return v;
    }

private:

    int N;  // number of nodes - for size() and isEmpty() methods
    NodePtr root;

    enum class Color {
        RED,
        BLACK
    };

    class Node{
        friend class LLRBT<Key, Item>;

        Key key;  //  The key needs to be modifiable for deletion implementation. So, no const like in the simple BST's case.
        Item value;
        Color color;
        NodePtr left, right;

        Node(const Key &k, Item v, Color c): key(k), value(v), color(c) { }
    };

    /// helper functions for put and get implementations
    NodePtr put(NodePtr x, const Key &key, Item value);
    NodePtr get(NodePtr x, const Key &key); // implementation is identical to BST

    /// helpers for remove key
    NodePtr remove(NodePtr node, const Key &key);

    // returns Node with max key
    NodePtr max(NodePtr x) {
        if (!x->right) return x;
        else return max(x->right);
    }

    // returns Node with minimum key in subtree with root x
    NodePtr min(NodePtr x) {
        if (!x->left) return x;
        else return min(x->left);
    }

    // deletes Node with minimum key in subtree with root x
    NodePtr removeMinNode(NodePtr x) {

        if(!x->left) return nullptr;

        if (!isRed(x->left) && !isRed(x->left->left))
            x = moveRedLeft(x);

        x->left = removeMinNode(x->left);

        return balance(x);
    }

    /// traversal functions. For now, I only have inorder

    /// The function is defined as a template over a boolean isItem, so that I can use it for both keys() and items() methods,
    /// that return different types (vector<Key> vs vector<Item>). This is just not to have to rewrite an almost identical inorder method.
    template <bool isItem>
    void inorder( NodePtr node, std::shared_ptr< std::vector< typename std::conditional<isItem, Item, Key>::type > > v );

    ///
    /// Color specific operations
    ///

    bool isRed(NodePtr node) {
        if(!node) return false;
        else return node->color == Color::RED;
    }

    // used for insertion and deletion
    NodePtr rotateLeft(NodePtr node);
    NodePtr rotateRight(NodePtr node);
    void flipColors(NodePtr node);

    //  used for deletion
    NodePtr moveRedLeft(NodePtr node);
    NodePtr moveRedRight(NodePtr node);
    NodePtr balance(NodePtr node);

};

/// recursive implementation of put function
template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::put(NodePtr node, const Key &key, Item value) {

    /// if we reach nullptr, it means that the key doesn't exist in the tree
    /// So, we create a new RED Node, update Node number, and return
    if(!node) { ++N; return NodePtr(new Node(key, value, Color::RED)); }

    /// if input key is smaller than current key, add (key, value) pair in left subtree
    /// if it is greater, in right subtree. If it is equal, then the key already exists, and we simply update the value
    if(key < node->key) node->left = put(node->left, key, value);
    else if(key > node->key) node->right = put(node->right, key, value);
    else node->value = value;

    //  Color specific operations

    if(!isRed(node->left) && isRed(node->right)) node = rotateLeft(node);
    if(isRed(node->left) && isRed(node->left->left)) node = rotateRight(node);
    if(isRed(node->left) && isRed(node->right)) flipColors(node);

    return node;
}

//
//  Color specific operations for insertion
//

//
//  LLRB trees are left-leaning, i.e. the red nodes are always left children
//  The method below is used when we have the opposite: black left child and red right child.
//
template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::rotateLeft(NodePtr node){

    NodePtr x = node->right;
    node->right = x->left;
    x->left = node;
    x->color = x->left->color;
    x->left->color = Color::RED;

    return x;
}

//
//  LLRB trees cannot have two red edges in a row, i.e. if a node is red, its children MUST be black
//  When it's not the case, we use rotateRight to restore the balance
//
template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::rotateRight(NodePtr node){

    NodePtr x = node->left;
    node->left = x->right;
    x->right = node;
    x->color = x->right->color;
    x->right->color = Color::RED;

    return x;
}

//
//  Nodes cannot have 2 RED children.
//  The method below is used to correct that kind of problem
//
template <typename Key, typename Item>
void LLRBT<Key, Item>::flipColors(NodePtr node){

    Color tmp = node->color;

    node->color = node->left->color;
    node->left->color = tmp;
    node->right->color = tmp;

    return;
}

/// recursively look for Node with a given key in the tree, and return a pointer to said Node when
//
//  get implementation is strictly identical to the BST one. We just ignore Color
//
template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::get(NodePtr node, const Key &key) {

    // if we reach a leaf, it means the key has not been found. So we return null
    if(!node) return nullptr;

    //  self-explanatory
    if(key < node->key) return get(node->left, key);
    else if(key > node->key) return get(node->right, key);
    else return node;
}

/// The remove method is the only one that is really (very) different than the BST case
template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::remove(NodePtr node, const Key &k) {

    if (k < node->key)  {
        if (!isRed(node->left) && !isRed(node->left->left))
            node = moveRedLeft(node);
        node->left = remove(node->left, k);
    }
    else {
        if (isRed(node->left))
            node = rotateRight(node);
        if (k == node->key && !(node->right))
            return nullptr;
        if ( !isRed(node->right) && !isRed(node->right->left) )
            node = moveRedRight(node);
        if (k == node->key) {
            NodePtr x = min(node->right);
            node->key = x->key;
            node->value = x->value;

            node->right = removeMinNode(node->right);
        }
        else node->right = remove(node->right, k);
    }
    return balance(node);
}

//
//  Color specific operations for remove
//

template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::moveRedLeft(NodePtr node){

    flipColors(node);

    if (isRed(node->right->left)) {
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
        flipColors(node);
    }

    return node;
}

template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::moveRedRight(NodePtr node){

    flipColors(node);

    if (isRed(node->left->left)) {
        node = rotateRight(node);
        flipColors(node);
    }
    return node;
}

template <typename Key, typename Item>
typename LLRBT<Key, Item>::NodePtr LLRBT<Key, Item>::balance(NodePtr node){

    if (isRed(node->right)) node = rotateLeft(node);
    if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node);
    if (isRed(node->left) && isRed(node->right)) flipColors(node);

    return node;
}

/// recursive implementation of In-order traversal for a BST. Pretty obvious
template <typename Key, typename Item> template <bool isItem>
void LLRBT<Key, Item>::inorder( NodePtr node, std::shared_ptr< std::vector< typename std::conditional<isItem, Item, Key>::type > > v) {

    if(!node) return;

    inorder<isItem>(node->left, v);
    v->push_back(isItem ? node->value : node->key); // if called from items() method, push_back the payload. Else push_back key
    inorder<isItem>(node->right, v);
}

#endif // LLRBT_H
