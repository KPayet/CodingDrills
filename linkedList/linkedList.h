#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class linkedList;
// helper class Node
template <typename T>
class Node {
    friend class linkedList<T>;
    typedef std::shared_ptr<Node<T> > NodeSharedPtr;
public:
    T data;
    NodeSharedPtr prev;
    NodeSharedPtr next;
    Node(T val, NodeSharedPtr p, NodeSharedPtr n):data(val), prev(p), next(n) {}
    ~Node(){}
}; // end class Node


template <typename T>
class linkedList {
private:
    typedef std::shared_ptr<Node<T> > NodeSharedPtr;
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
        first = NodeSharedPtr(new Node<T>(data, nullptr, first));
        if(!last)
            last = first;
        ++N;
    }
    void addLast(T data) {
        if(!last) {
            addFirst(data);
            return;
        }
        last->next = NodeSharedPtr(new Node<T>(data, last, nullptr));
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

    //overloading ostream operator to be able to use std::cout<<myLinkedList;
    // Works as long as your type T overloads std::ostream& operator<< ...
    friend std::ostream& operator<< (std::ostream &out, const linkedList &lList){
        if(!lList.N) {
            out<<" ";
            return out;
        }
        NodeSharedPtr x = lList.first;
        while(x) {
            out<<x->data<<" ";
            x = x->next;
        }
        return out;
    }
    friend std::ostream& operator<< (std::ostream &out, const linkedList *lList){
        out<<*lList;
        return out;
    }
}; // end class linkedList
#endif // LINKEDLIST_H
