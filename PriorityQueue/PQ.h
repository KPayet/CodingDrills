#ifndef PQ_H
#define PQ_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// PQ.H
// This file is a template class implementation for the priority queue data structure
// It offers both MaxPQ and MinPQ which are just aliases defined from the main class implementation
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

class PQ {

public:

    /// Constructors + Destructor
    PQ() {}
    PQ(int maxN) {}

    ~PQ() {}

    /// Functions that access data/ modify data structure

    void enqueue(int data);
    /// returns and remove min/max element from the queue
    int dequeue();
    int peek(); // just returns min/max element without

    /// diagnostics

    int size();
    bool isEmpty();

};

#endif // PQ_H
