#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include <cassert>

///
/// Simple Queue template class, not double-ended
/// The class is built upon a doubly-linked list
/// See LinkedList/LinkedList.h
///
/// I thought about adding an iterator to the class, to be able to use range-based for
/// i.e. loop, and dequeue each item on at a time
/// But I judged that the user can do that pretty easily, e.g. while(!q.isEmpty()) T item = q.dequeue(); ...
/// I might do it later, strictly for the exercise
///
template <class T>
class Queue
{
private:

    ///
    /// Internal linked list the queue is based upon.
    /// As you will see below, it is this class that does all the work
    /// The Queue class is simply just ensuring that the list is used FIFO-style
    /// For more details about that class, see ../LinkedList/LinkedList.h
    ///
    LinkedList<T> internalList; /// the list is dynamic.

public:

        ///
        /// Constructors/Destructor
        ///

        /// Right now the Queue is only designed to be built empty, and items enqueued when needed
        /// Could add constructor from an array, vector... but the user can do that easily on its own.
        Queue() {}
        virtual ~Queue() {}

        ///
        /// enqueue and dequeue operations
        /// Queue is a FIFO access type data structure
        /// This can be implemented easily by adding last for enqueue
        /// and removing first for dequeue
        ///
        void enqueue(T v) {
            internalList.addLast(v);
        }

        /// Here, we have to assert that the user doesn't try to dequeue from an empty Queue
        /// Either use assert, or simply do nothing.
        /// I feel assert is better because it tells the user that he might be doing something weird
        T dequeue() {
            assert(!this->isEmpty() && "Trying to dequeue from empty Queue!"); /// stop execution if trying to dequeue from empty queue

            /// pop front
            T item = internalList.getFront();
            internalList.removeFirst();

            return item;
        }

        /// Empty Queue
        /// Simply use the clear routine in list implementation
        void clear() {
            internalList.clear();
        }

        ///
        /// Members that don't modify the Queue
        /// Could be const functions, but I don't really see the point of declaring a const Queue
        ///

        /// If you want to see the next item to be dequeued
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

#endif // QUEUE_H
