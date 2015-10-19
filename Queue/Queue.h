#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include <cassert>

///
/// Simple Queue class, not double-ended
/// The class is built upon a doubly-linked list
/// See LinkedList/LinkedList.h
///
class Queue
{
private:

    ///
    /// Internal linked list the queue is based upon.
    /// As you will see below, it is this class that does all the work
    /// The Queue class is simply just ensuring that the list is used FIFO-style
    /// For more details about that class, see ../LinkedList/LinkedList.h
    ///
    LinkedList<int> intList; /// the list is dynamic.

public:

        ///
        /// Constructors
        ///
        Queue() {}
        virtual ~Queue() {}

        ///
        /// enqueue and dequeue operations
        /// Queue is a FIFO access type data structure
        /// This can be implemented easily by adding last for enqueue
        /// and removing first for dequeue
        ///
        void enqueue(int v) {
            intList.addLast(v);
        }

        int dequeue() {
            assert(!this->isEmpty() && "Trying to dequeue from empty Queue!");
            int item = intList.getFront();
            intList.removeFirst();

            return item;
        }

        /// Empty Queue
        /// Simply use the clear routine in list implementation
        void clear() {
            intList.clear();
        }

        ///
        /// Members that don't modify the Queue
        /// Could be const functions, but I don't really see the point of declaring a const Queue
        ///

        /// If you want to see the next item to be dequeued
        /// but don't want it removed
        int peek() {
            return intList.getFront();
        }

        int size() { /// self-explanatory
            return intList.size();
        }

        bool isEmpty() {
            return intList.isEmpty();
        }
};

#endif // QUEUE_H
