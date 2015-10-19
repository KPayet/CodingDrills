#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

///
/// Simple Queue class, not double-ended
/// The class is built upon a doubly-linked list
/// See LinkedList/LinkedList.h
///
class Queue
{
private:

    ///
    /// Internal linked list the queue is based upon
    /// For more details about that class, see ../LinkedList/LinkedList.h
    ///
    LinkedList<int> intList;

    public:

        ///
        /// Constructors
        ///
        Queue();
        virtual ~Queue();

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
            int item = l.first->data;
            l.removeFirst();
        }

    private:
};

#endif // QUEUE_H
