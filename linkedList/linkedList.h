// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// LinkedList.H
// declares a custom linked list template class that implement STL-style iterator, for use with range-based for loop.
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <iterator>

//
//  Declaration of a custom linked list class
//  Example:
//  std::vector<double> a = {1.5, 2.5, 3.0, 4.9, 5.55, 5.154};
//  linkedList<double> l1(a);
//  LinkedList *l2<int> = new LinkedList<int>();
//
//  for(auto x: l1)
//      l2->addFirst(x);
//
template <class T>
class linkedList {

private:

    class Node;
    typedef std::shared_ptr<Node> NodeSharedPtr;

    //helper class Node
    class Node {

    public:
        T data;
        NodeSharedPtr prev;
        NodeSharedPtr next;
        Node(T val, NodeSharedPtr p, NodeSharedPtr n):data(val), prev(p), next(n) {}
    }; // end class Node

    template <bool isConst>
    class listIter : public std::iterator<std::forward_iterator_tag, T>
    {
    private:

        typedef typename std::conditional<isConst, const T&, T&>::type ValueReferenceType;
        NodeSharedPtr itr;

    public:

        listIter(): itr(nullptr) { }

        listIter(NodeSharedPtr n): itr(n) { }

        listIter(const listIter<isConst>& other) : itr(other.itr) { }

        listIter& operator++(){
            assert(itr != nullptr && "Out-of-bounds iterator increment!");
            itr = itr->next;
            return *this;
        }

        listIter operator++(int){
            assert(itr != nullptr && "Out-of-bounds iterator increment!");
            listIter tmp(*this);
            itr = itr->next;
            return tmp;
        }

        bool operator==(const listIter& rhs) const {
            return itr == rhs.itr;
        }

        bool operator != (const listIter& rhs) const {
            return itr != rhs.itr;
        }

        ValueReferenceType operator*() const{
            assert(itr != nullptr && "Invalid iterator dereference!");
            return itr->data;
        }

        ValueReferenceType operator->() const{
            assert(itr != nullptr && "Invalid iterator dereference!");
            return itr->data;
        }
    }; // end class listIter

    typedef listIter<false> iterator;
    typedef listIter<true> const_iterator;

    NodeSharedPtr first;
    NodeSharedPtr last;
    int N;

public:

    linkedList() {
        N=0;
    }

    linkedList(std::vector<T> &v) {
        N=0;
        for(auto x: v)
            addLast(x);
    }

    linkedList(const linkedList &cSource) { // copy constructor
        // implement me :(
    }

    ~linkedList() {
        while(N)
            removeFirst();
    }

    void addFirst(T data) {
        first = NodeSharedPtr(new Node(data, nullptr, first));
        if(!last)
            last = first;
        ++N;
    }

    void addLast(T data) {
        if(!last) {
            addFirst(data);
            return;
        }
        last->next = NodeSharedPtr(new Node(data, last, nullptr));
        last = last->next;
        ++N;
    }

    void removeFirst() {
        if(!first) return;
        if(!first->next) {
            first = nullptr;
            last = nullptr;
            --N;
            return;
        }
        first = first->next;
        first->prev = nullptr;
        --N;
    }

    void removeLast() {
        if(!last) return;
        if(!last->prev){
            first = nullptr;
            last = nullptr;
            --N;
            return;
        }
        last = last->prev;
        last->next = nullptr;
        --N;
    }

    void clear() {
        while(N)
            removeFirst();
    }

    int size() {
        return N;
    }

    bool isEmpty() {
        return N==0;
    }

    void print() {
        if(!N) return;
        NodeSharedPtr x = first;
        while(x) {
            std::cout<<x->data<<" ";
            x = x->next;
        }
        std::cout<<std::endl;
    }

    iterator begin() {
        return iterator(first);
    }

    iterator end() {
        return iterator(nullptr);
    }

    template <class T2>
    friend iterator begin(linkedList<T2> *l){
        return (*l).begin();
    }

    template <class T2>
    friend iterator end(linkedList<T2> *l) {
        return (*l).end();
    }

}; // end class linkedList
#endif // LINKEDLIST_H
