// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// Stack.h
// declares a simple stack template class.
// This is one is dynamic array based implementation.
// No iterator is implemented, but I might do it later for fun.
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------
#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <vector>

///
/// Simple Stack template class, not double-ended.
/// The class uses the dynamic array based implementation.
/// The API is obviously the same as the linked-list based implementation.
/// Only the internals change: use array to hold items + top and capacity variables + add functions to resize
/// in push or pop functions + the functions in the private section.
/// However, I can also cheat and use an std::vector as internal array, and let it do all the resizing needed...
///
/// I thought about adding an iterator to the class, to be able to use range-based for
/// i.e. loop, and pop each item on at a time
/// But I judged that the user can do that pretty easily, e.g. while(!s.isEmpty()) T item = s.pop(); ...
/// I might do it later, strictly for the exercise
///
template <class T>
class Stack
{
private:

    ///
    /// I use an std::vector as internal array.
    /// This way, I can let it do all the resizing
    /// Or, I can simply do the resizing (doubling and halving) explicitly
    /// with reserve functions...
    /// But actually, like in the Queue case, the internal container (here vector) does all the work
    /// The Stack class simply enforces the LIFO access...
    ///
    std::vector<T> internalArray;
    //int top; /// needed to access element to be popped
    //int capacity; /// usually needed in array implementation on stacks. But I'm using vector...


public:

        ///
        /// Constructors/Destructor
        ///

        /// Right now the Stack is only designed to be built empty, and items pushed when needed
        /// Could add constructor from an array, vector... but the user can do that easily on its own.
        Stack() {}
        virtual ~Stack() {}

        ///
        /// push and pop operations
        /// Stack is a LIFO access type data structure
        ///
        void push(T v) {
            internalArray.push_back(v);
        }

        /// Here, we have to assert that the user doesn't try to pop from an empty Stack
        /// Either use assert, or simply do nothing.
        /// I feel assert is better because it tells the user that he might be doing something weird
        T pop() {
            assert(internalArray.size() && "Trying to pop from empty Stack!"); /// stop execution if trying to pop from empty stack

            T item = internalArray.back();
            internalArray.pop_back();

            return item;
        }

        /// Empty Stack
        /// Simply use the clear routine in vector implementation
        void clear() {
            internalArray.clear();
            //top = 0;
        }

        ///
        /// Members that don't modify the Stack
        /// Could be const functions, but I don't really see the point of declaring a const Stack
        ///

        /// If you want to see the next item to be popped
        /// but don't want it removed
        T peek() {
            return internalArray.back();
        }

        int size() {    /// self-explanatory
            return internalArray.size();
        }

        bool isEmpty() {    /// idem
            return internalArray.size() == 0;
        }
};

#endif // STACK_H
