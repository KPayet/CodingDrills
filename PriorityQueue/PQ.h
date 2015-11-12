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

#include <vector>

class PQ {

private:
    int N;  // queue size
    std::vector<int> pq;

    ///helper functions

    void exch(const int i, const int j); // swaps items pq[i] and pq[j]
    // this function is in charge of the comparison (i.e. < or > ?)
    bool heapCompare(int a, int b){ // true if

    }

    /// helper functions used to implement insert and get
    /// swim and sink move the item respectively up and down the heap,
    /// until the heap property is satisfied.
    void swim(int i){
        // while heap property is not satisfied between i and its parent,
        // swap both elements
        while(i > 1 && pq[i] > pq[i/2]){
            exch(i, i/2);
            i = i/2;
        }
    }
    void sink(int i);

public:

    /// Constructors + Destructor
    PQ(): N(0) {
        pq[0] = nullptr;
    }
    PQ(int maxN):PQ(){
        pq.reserve(maxN);
        pq[0] = nullptr;
    }

    ~PQ() {}

    /// Functions that access data/ modify data structure

    void enqueue(int data){
        pq[++N] = data;
        swim(N);
    }
    /// returns and remove min/max element from the queue
    int dequeue(){
        int item = pq[1]; // min or max depending on the type of queue
        exch(1, N--);
        sink(1);
        pq.erase(N+1);
        return item;
    }
    int peek(){ // just returns min/max element without
        return pq[1];
    }

    /// diagnostics

    int size(){ return N;}
    bool isEmpty(){ return N == 0;}
};

#endif // PQ_H
