#ifndef HASHTABLE_H
#define HASHTABLE_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// HashTable.H
//  This file declares a template class that describes a hash table, i.e. associative array
//
//  The advantage of hash tables over tree based associative arrays is speed.
//  Through hashing, a hash table allows for constant time basic operations, i.e. insert, search, delete.
//
//  However, we loose the ability to perform any ordered operation (min, max, rank ...).
//  If that kind of operations are required, then it is better to turn to LLRBT implementation of associative array.
//
//  One of the most vital pieces of a hash table implementation is the hash function used.
//  The latter must have some properties, such as uniform distribution of hash values (or close), it must be deterministic,
//  it uses all input data ...
//  In this implementation, I won't be implementing my own hash function, but instead use

//  This implementation uses the separate chaining method for resolving collision, i.e. the buckets are represented by some array,
//  and the elements of each buckets are linked-list where each Node holds a key-value pair
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <memory>
#include <vector>
#include <functional>

template <typename Key, typename Item>
class HashTable {

public:

    /// Constructors
    // We can think of 3 types of constructors that can be useful

    //  Default
    HashTable() {
        N = 0;
        M = 1021;    // well, why not ?
    }

    //  When the user knows approximately how many keys will be used, and wants us to find perfect number of buckets
    HashTable(int nKeys): N(0) {
        M = static_cast<int>(nKeys/0.75) + 1;    // I specify a hash table that will have a load factor of .75 max
    }

    void put(const Key &key, Item value);
    Item *get(const Key &key);
    void remove(const Key &key);

    bool contains(const Key &key) {
        if(!get(key)) return false;
        return true;
    }
    int size() {return N;}
    bool isEmpty() { return N == 0;}

private:

    class Node;
    typedef std::shared_ptr<Node> NodePtr;

    int N;  //  number of keys
    int M;   // number of buckets

    //  the symbol table is represented as a vector of Node, where st[i] is the first Node of
    //  a linked-list composed of all key-value pairs that hashed to bucket i
    std::vector<NodePtr> st;

    //  We also need to declare a Node abstraction
    class Node {
        friend class HashTable<Key, Item>;

        Key key;
        Item value;

        NodePtr next;
        NodePtr prev;   // we define a doubly-linked list

        Node(const Key &k, Item v, NodePtr n = nullptr, NodePtr p = nullptr): key(k), value(v), next(n), prev(p) {}
    };

    std::hash<Key> hash;
};

#endif // HASHTABLE_H
