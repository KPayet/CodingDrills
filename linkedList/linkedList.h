#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <vector>

class linkedList {
private:

    // helper class Node
    class Node {
    public:
        int data;
        Node *prev;
        Node *next;
        Node(int val, Node* p, Node* n):data(val), prev(p), next(n) {}
        ~Node(){}
    }; // end class Node
    Node *first;
    Node *last;
    int N;
public:

    linkedList() {
        first = nullptr;
        last = nullptr;
        N=0;
    }
    linkedList(std::vector<int> &v) {
        first = nullptr;
        last = nullptr;
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
        delete first;
        delete last;
    }
    void addFirst(int data) {
        first = new Node(data, nullptr, first);
        if(!last)
            last = first;
        ++N;
    }
    void addLast(int data) {
        if(!last) {
            addFirst(data);
            return;
        }
        last->next = new Node(data, last, nullptr);
        last = last->next;
        ++N;
    }
    void removeFirst() {
        if(!first) return;
        if(!first->next) {
            delete first;
            first = nullptr;
            last = nullptr;
            --N;
            return;
        }
        Node *oldfirst = first;
        first = first->next;
        first->prev = nullptr;
        delete oldfirst;
        oldfirst = 0;
        --N;
    }
    void removeLast() {
        if(!last) return;
        if(!last->prev){
            delete last;
            first = nullptr;
            last = nullptr;
            --N;
            return;
        }
        Node *oldlast = last;
        last = last->prev;
        last->next = nullptr;
        delete oldlast;
        oldlast = 0;
        --N;
    }
    int size() {
        return N;
    }
    bool isEmpty() {
        return N==0;
    }

    //overloading ostream operator to be able to use std::cout<<myLinkedList;
    friend std::ostream& operator<< (std::ostream &out, const linkedList &lList){
        if(!lList.N) {
            out<<" ";
            return out;
        }
        Node *x = lList.first;
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
};
#endif // LINKEDLIST_H
