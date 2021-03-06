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

///
/// Declaration of generic template priority queue class
/// isMax boolean controls if we want a MinPQ (priority to smaller elements) or MaxPQ
/// Note that two aliases are defined at the bottom of this file: MinPQ and MaxPQ, that should be used by the user
///
template <class T, bool isMax> // isMax == true => we need MaxPQ
class PQ {

/// I declare protected constructors, because I want the class to be accessed through the MinPQ and MaxPQ specialized classes only (see bottom)
protected:

    /// Constructors + Destructor
    PQ(): N(0) {}

    PQ(int maxN){
        pq.reserve(maxN);
        N = 0;
    }

    ~PQ() {}

public:

    /// Functions that access data/ modify data structure

    void enqueue(T data){
        pq.push_back(data);
        swim(N++);
    }
    /// returns and remove min/max element from the queue
    T dequeue(){
        T item = pq[0]; // min or max depending on the type of queue
        exch(0, --N);
        sink(0);
        pq.erase(pq.begin() + N);
        return item;
    }

    T peek(){ // just returns min/max element without
        return pq[0];
    }

    /// diagnostics

    int size(){ return N;}
    bool isEmpty(){ return N == 0;}

private:
    int N;  // queue size
    std::vector<T> pq; // actually holds the elements

    ///helper functions

    void exch(const int i, const int j){ // swaps items pq[i] and pq[j]
        T tmp = pq[i];
        pq[i] = pq[j];
        pq[j] = tmp;
    }
    // this function is in charge of the comparison (i.e. < or > ?)
    // this is where we tell that we want a Min or MaxPQ
    // ALl it takes is inverting the direction of the comparison operator
    bool heapOrdered(int a, int b){

        return isMax ? pq[a] < pq[b] : pq[a] > pq[b];
    }

    /// helper functions used to implement insert and get
    /// swim and sink move the item respectively up and down the heap,
    /// until the heap property is satisfied.
    void swim(int i){
        // while heap property is not satisfied between i and its parent,
        // swap both elements
        int p = i%2 == 0 ? i/2-1 : i/2;
        while(i > 0 && !heapOrdered(i, p)){
            exch(i, p);
            i = p ;
            p = i%2 == 0 ? i/2-1 : i/2;
        }
    }

    void sink(int i){
        /// repeatedly move element down the heap until heap property is once again satisfied
        while (2*i+1 <= N-1)
        {
            int j = 2*i+1; // in a binary heap, children of i are in indexes 2*i+1 and 2*i+2
            if (j < N-1 && !heapOrdered(j+1, j)) j++; // select largest of two children
            if (heapOrdered(j, i)) break;   // if pq[i] is larger than the largest child, then it's all good
            exch(i, j);
            i = j;
        }
    }
};

/// Aliases to be used by the user to create a Min or MaxPQ
/// First I simply created aliases with using MinPQ = PQ<T, false>; ...
/// But I couldn't find a way to limit access to PQ itself
/// By creating two new classes, that simply specializes PQ (for isMax = true/false),
/// I can hide PQ, and have users call only MinPQ and MaxPQ - Is there a simpler way?
template <class T>
class MaxPQ: public PQ<T, true> {
public:
    MaxPQ() {}
    MaxPQ(int maxN): PQ<T, true>(maxN) {}
};

template <class T>
class MinPQ: public PQ<T, false> {
public:
    MinPQ() {}
    MinPQ(int maxN): PQ<T, false>(maxN) {}
};

#endif // PQ_H
