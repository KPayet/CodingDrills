#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

template <class T>
class linkedList {

private:

    class Node {
    friend class linkedList<T>;
        typedef std::shared_ptr<Node> NodeSharedPtr;

    public:
        T data;
        NodeSharedPtr prev;
        NodeSharedPtr next;
        Node(T val, NodeSharedPtr p, NodeSharedPtr n):data(val), prev(p), next(n) {}
        ~Node(){}
    }; // end class Node

    typedef std::shared_ptr<Node> NodeSharedPtr;
    NodeSharedPtr first;
    NodeSharedPtr last;
    int N;

    template <bool is_const_iterator = true>
    class const_noconst_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        typedef typename std::conditional<is_const_iterator, const linkedList*, linkedList*>::type DataStructurePointerType;
        typedef typename std::conditional<is_const_iterator, const T&, T&>::type ValueReferenceType;

        Node* itr;
        explicit const_noconst_iterator(Node* nd) : itr(nd) { }

    public:

        const_noconst_iterator(): itr(nullptr) { }

        const_noconst_iterator(const const_noconst_iterator<false>& other) : itr(other.itr)
        {
        }

        void swap(const_noconst_iterator& other) noexcept {
            std::swap(itr, other.iter);
        }

        const_noconst_iterator& operator++(){
            assert(itr != nullptr && "Out-of-bounds iterator increment!");
            itr = itr->next;
            return *this;
        }

        const_noconst_iterator operator++(int){
            assert(itr != nullptr && "Out-of-bounds iterator increment!");
            const_noconst_iterator tmp(*this);
            itr = itr->next;
            return tmp;
        }

        bool operator==(const const_noconst_iterator& rhs) const {
            return itr == rhs.itr;
        }

        bool operator != (const const_noconst_iterator& rhs) const {
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

//        // One way conversion: iterator -> const_iterator
//        operator const_noconst_iterator<const Type>() const{
//            return const_noconst_iterator<const Type>(itr);
//        }
        friend class const_noconst_iterator<true>;
    }; // end class const_noconst_iterator

    // `iterator` and `const_iterator` used by your class:
    typedef const_noconst_iterator<false> iterator;
    typedef const_noconst_iterator<true> const_iterator;

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
