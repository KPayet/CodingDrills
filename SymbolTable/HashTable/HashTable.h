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
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <memory>
#include <vector>

template <typename Key, typename Item>
class HashTable {

public:

    void put(const Key &key, Item value);
    Item *get(const Key &key);
    void remove(const Key &key);

    bool contains(const Key &key);
    int size();
    bool isEmpty();

private:

    int hash(const Key &key);
};

#endif // HASHTABLE_H
