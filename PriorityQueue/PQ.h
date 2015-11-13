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
// We use a binary heap implementation here:
//  our data elements are represented as a binary tree, that satisfies the heap property,
//  i.e. If A is a parent node of B then the key of node A is ordered with respect to the key of
//  node B with the same ordering applying across the heap. e.g. for a max heap, A is always larger than both children.
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <vector>

class PQ {

public:

    /// Constructors + Destructor
    PQ(): N(0) {}

    PQ(int maxN){
        pq.reserve(maxN);
        N = 0;
    }

    ~PQ() {}

    /// Functions that access data/ modify data structure

    void enqueue(int data){
        pq.push_back(data);
        swim(N++);
    }
    /// returns and remove min/max element from the queue
    int dequeue(){
        int item = pq[0]; // min or max depending on the type of queue
        exch(0, --N);
        sink(0);
        pq.erase(pq.begin() + N);
        return item;
    }
    int peek(){ // just returns min/max element without
        return pq[0];
    }

    /// diagnostics

    int size(){ return N;}
    bool isEmpty(){ return N == 0;}

private:
    int N;  // queue size
    std::vector<int> pq;

    ///helper functions

    void exch(const int i, const int j){ // swaps items pq[i] and pq[j]
        int tmp = pq[i];
        pq[i] = pq[j];
        pq[j] = tmp;
    }
    // this function is in charge of the comparison (i.e. < or > ?)
    bool heapCompare(int a, int b){ // true if

    }

    /// helper functions used to implement insert and get
    /// swim and sink move the item respectively up and down the heap,
    /// until the heap property is satisfied.
    void swim(int i){
        // while heap property is not satisfied between i and its parent,
        // swap both elements
        int p = i%2 == 0 ? i/2-1 : i/2;
        while(i > 0 && pq[i] > pq[p]){
            exch(i, p);
            i = p ;
            p = i%2 == 0 ? i/2-1 : i/2;
        }
    }

    void sink(int i){
        while (2*i+1 <= N)
        {
            int j = 2*i+1; // in a binary heap, children of i are in indexes 2*i+1 and 2*i+2
            if (j < N && pq[j] < pq[j+1]) j++; // select largest of two children
            if (pq[i] > pq[j]) break;   // if pq[i] is larger than the largest child, then it's all good
            exch(i, j);
            i = j;
        }
    }
};

#endif // PQ_H
