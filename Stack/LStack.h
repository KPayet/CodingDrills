// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// LStack.h
// declares a simple stack template class, with linked list implementation.
// No iterator is implemented, but I might do it later for fun.
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------
#ifndef LSTACK_H
#define LSTACK_H

#include "LinkedList.h"
#include <cassert>

///
/// Simple LStack template class, not double-ended
/// The class is built upon a doubly-linked list
/// See LinkedList/LinkedList.h
///
/// I thought about adding an iterator to the class, to be able to use range-based for
/// i.e. loop, and pop each item on at a time
/// But I judged that the user can do that pretty easily, e.g. while(!s.isEmpty()) T item = s.pop(); ...
/// I might do it later, strictly for the exercise
///
template <class T>
class LStack
{
private:

    ///
    /// Internal linked list the stack is based upon.
    /// As you will see below, it is this class that does all the work
    /// The LStack class is simply just ensuring that the list is used LIFO-style
    /// For more details about that class, see ../LinkedList/LinkedList.h
    ///
    LinkedList<T> internalList; /// the list is dynamic.

public:

        ///
        /// Constructors/Destructor
        ///

        /// Right now the LStack is only designed to be built empty, and items pushd when needed
        /// Could add constructor from an array, vector... but the user can do that easily on its own.
        LStack() {}
        virtual ~LStack() {}

        ///
        /// push and pop operations
        /// LStack is a LIFO access type data structure
        /// This can be implemented easily by adding first for push
        /// and removing first for pop
        ///
        void push(T v) {
            internalList.addFirst(v);
        }

        /// Here, we have to assert that the user doesn't try to pop from an empty LStack
        /// Either use assert, or simply do nothing.
        /// I feel assert is better because it tells the user that he might be doing something weird
        T pop() {
            assert(!this->isEmpty() && "Trying to pop from empty LStack!"); /// stop execution if trying to pop from empty stack

            /// pop front
            T item = internalList.getFront();
            internalList.removeFirst();

            return item;
        }

        /// Empty LStack
        /// Simply use the clear routine in list implementation
        void clear() {
            internalList.clear();
        }

        ///
        /// Members that don't modify the LStack
        /// Could be const functions, but I don't really see the point of declaring a const LStack
        ///

        /// If you want to see the next item to be popped
        /// but don't want it removed
        T peek() {
            return internalList.getFront();
        }

        int size() {    /// self-explanatory
            return internalList.size();
        }

        bool isEmpty() {    /// idem
            return internalList.isEmpty();
        }
};

#endif // LSTACK_H
