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

///
///  Declaration of a custom linked list class
///  Example:
///  std::vector<double> a = {1.5, 2.5, 3.0, 4.9, 5.55, 5.154};
///  LinkedList<double> l1(a);
///  LinkedList *l2<int> = new LinkedList<int>();
///
///  for(auto x: l1)
///      l2->addFirst(x);
///
template <class T>
class LinkedList {

private:

    /// Forward declaration of class Node that is used internally by LinkedList
    /// Simply to define the NodeSharedPtr alias, that is used in subsequent implementation
    class Node;
    typedef std::shared_ptr<Node> NodeSharedPtr; // use of shared_ptr for easier memory usage

    ///
    /// helper class Node
    /// Simple nested class used to build the LinkedList class
    /// Each Node has a link to the next and previous Nodes, which makes LinkedList doubly linked
    ///
    class Node {

    public:

        ///
        /// The data carried by each Node
        /// Note that the data is stored by value (i.e. we don't simply keep a reference or link to it)
        /// If the user wants to keep only pointers, he must ask it explicitly:
        /// e.g. LinkedList<SomeClass*> *l = ...
        ///
        T data;

        ///
        /// prev and next point respectively to the next and previous Nodes in the LinkedList
        /// The implementation doesn't use sentinel node.
        /// First and last node have respectively prev and next set to nullptr
        ///
        NodeSharedPtr prev;
        NodeSharedPtr next;

        Node(T val, NodeSharedPtr p, NodeSharedPtr n):data(val), prev(p), next(n) {}
    }; // end class Node

    ///
    /// Definition of an iterator for the LinkedList class
    /// I wanted the LinkedList class instances to be able to use range-based for syntax
    ///
    /// The isConst template parameter is used to identify if we want a const iterator or not
    /// At the end of the class, the const_iterator and iterator aliases are defined,
    /// respectively for ListIter<true> and ListIter<false>
    ///
    template <bool isConst>
    class ListIter : public std::iterator<std::forward_iterator_tag, T>
    {
    private:

        ///
        /// Test on isConst, and define type ValueReferenceType to either const T& or T& depending on its value
        /// Doing it this way allows to define both iterators (const and non const), without duplicating code
        ///
        typedef typename std::conditional<isConst, const T&, T&>::type ValueReferenceType;

        ///
        /// Tells which Node in the LinkedList our iterator is pointing to at the moment
        ///
        NodeSharedPtr itr;

    public:

        ///
        /// The Constructors for the iterator class
        /// Pretty basic
        ///
        ListIter(): itr(nullptr) { } /// implemented out of habit, but actually never used in the

        ListIter(NodeSharedPtr n): itr(n) { }

        ListIter(const ListIter<isConst>& other) : itr(other.itr) { }

        ///
        /// To implement a STL-style iterator, there are a few requirements regarding the operators to overload:
        /// operator++, pre- and post-increment
        /// comparison operators: assignment and !=
        /// Dereference operator. Also a good idea to have operator->
        ///

        ///
        /// operator++
        /// Simply make the iterator point to the next Node in the LinkedList
        ///
        ListIter& operator++(){ /// pre-increment ++
            assert(itr != nullptr && "Out-of-bounds iterator increment");
            itr = itr->next;
            return *this;
        }

        ListIter operator++(int){ /// post-increment. uses pre-increment operator
            assert(itr != nullptr && "Out-of-bounds iterator increment");
            ListIter tmp(*this);
            itr = itr->next;
            return tmp;
        }

        ///
        /// Comparison operators
        /// Both are const, for const correctness
        ///

        bool operator==(const ListIter& other) const {
            return itr == other.itr;
        }

        bool operator != (const ListIter& other) const {
            return itr != other.itr;
        }

        ///
        /// Dereference and -> operators
        /// Both are made const too, for const correctness
        /// Returns the data carried by the current Node the iterator is pointing to
        ///

        ValueReferenceType operator*() const{
            assert(itr != nullptr && "Invalid iterator dereference");
            return itr->data;
        }

        ValueReferenceType operator->() const{
            assert(itr != nullptr && "Invalid iterator dereference");
            return itr->data;

        ///
        /// And that's it for this class
        ///
        }
    }; // end class ListIter

    ///
    /// Like I said above, define aliases iterator and const_iterator for range-based for to use
    ///
    typedef ListIter<false> iterator;
    typedef ListIter<true> const_iterator;


    ///
    /// We finally get to the private members of the LinkedList class itself
    /// first and last point to the first and last Node of the list respectively
    /// For empty list, first = last = nullptr
    /// I also keep an integer N, initialized at zero, and incremented each time a node is added, for the size
    ///
    NodeSharedPtr first;
    NodeSharedPtr last;

    int N;

public:

    ///
    /// Constructors
    ///

    LinkedList() {  /// create empty LinkedList by setting N to 0.
        N=0;        /// Doesn't have to explicitly set first and last to nullptr, but let shared_ptr deal with it.
    }

    /// Create LinkedList by copying values from vector
    /// I simply added support for vectors, because that's what you should use most of the time
    /// And since user is me :), well I know I will do it...
    LinkedList(std::vector<T> &v) : LinkedList() {
        for(auto x: v)
            addLast(x); /// we need to addLast, to preserve the order of the input vector
    }

    LinkedList(const LinkedList &cSource) : LinkedList() { /// copy constructor
        for(auto x: cSource)    /// that's why implementing iterator above is neat
            addLast(x);
    }

    ///
    /// Destructor
    /// I simply remove every Node one at a time, i.e., stop pointing to it (see remove functions)
    /// shared_ptr deals with the memory
    ///
    ~LinkedList() {
        while(N)
            removeFirst();
    }

    ///
    /// Functions to add Nodes to our list, from...
    ///

    void addFirst(T data) { /// ...the start of the list.
        /// adding a new Node first, is simply creating a Node that points to current to nullptr (prev), and current first (next)
        first = NodeSharedPtr(new Node(data, nullptr, first));

        if(!last) /// i.e. if the list was empty, and has now one Node
            last = first;
        ++N;
    } // addFirst

    void addLast(T data) {  /// ...or the end.
        /// if list is empty, we call to addFirst above
        if(!last) {
            addFirst(data);
            return;
        }
        /// if not, adding a new Node in last position is simply creating a Node that points to last (prev) and to nullptr (next)
        last->next = NodeSharedPtr(new Node(data, last, nullptr));
        last = last->next;  /// and officially making it the new last Node of the list. Congrats!
        ++N;
    } // addLast

    ///
    /// Functions to remove Nodes from our list.
    /// We remove from...
    ///
    void removeFirst() {    /// ...the beginning of the list, stack-style.
        /// if list is empty do nothing
        if(!first) return;

        /// if there is only one Node in the list, i.e. first = last, and both point to nullptr (prev and next),
        /// set first and last links to nullptr, and let shared_ptr clean the memory.
        if(!first->next) {
            first = nullptr;
            last = nullptr;
            --N;
            return;
        }
        /// else, if we have at least two Nodes
        /// Simply bypass the first Node (make the second Node first)
        /// and make second Node (now first) point to nullptr
        /// again shared_ptr deals with memory
        ///
        first = first->next;
        first->prev = nullptr;

        --N;
    } // removeFirst

    void removeLast() { /// ...the end of the list, queue-style.
        /// the cases are the same.
        /// if list is empty
        if(!last) return;

        /// if only one Node
        if(!last->prev){
            removeFirst();  /// no duplicate
        }
        /// else make last point to current penultimate Node
        /// and remove link of new last to next (from previous penultimate to previous last)
        last = last->prev;
        last->next = nullptr;

        --N;
        }

    ///
    /// I need two functions to access the data from the first and last Nodes
    /// This will help for implementing queue for example
    ///
    T getFront() {
        return first->data;
    }

    T getTail() {
        return last->data;
    }

    /// remove all Nodes from list
    void clear() {
        while(N)
            removeFirst();
    }

    int size() {    // self-explanatory
        return N;
    }

    bool isEmpty() {    // idem
        return N==0;
    }

    /// print all data values in the list
    void print() {
        if(!N) return;

        for(auto x: this) {
            std::cout<<x<<" ";
        }
        std::cout<<std::endl;
    }

    ///
    /// begin and end member functions used by range-based for
    /// The two last one are so it can also be used on pointers:
    /// LinkedList *l = new LinkedList(a);
    /// for(auto x: l) { ... }
    ///
    /// Otherwise, it didn't work.
    ///
    /// With (auto x: l), x is not modifiable
    /// To modify data from the list, use (auto &x: l)
    ///
    iterator begin() {  /// for( auto x = l.begin(); ...
        return iterator(first);
    }

    iterator end() {    /// ...x != l.end(); x++) { ... }
        return iterator(nullptr);
    }

    template <class T2>
    friend iterator begin(LinkedList<T2> *l){
        return (*l).begin();
    }

    template <class T2>
    friend iterator end(LinkedList<T2> *l) {
        return (*l).end();
    }

}; // end class LinkedList
#endif // LINKEDLIST_H
