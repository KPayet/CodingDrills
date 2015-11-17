#ifndef HEAPSORT_H
#define HEAPSORT_H


// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// heapsort.h
// This header simply implements a template sorting function, using heapsort algorithm
// It can be used to sort any type that implements comparison operators
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

// This algorithm reuses the components of priority queue implementation
//  namely, the sink and sink and exch function.
//  HeapSorting is simply reordering an array so that it satisfies heap property,
//  and then perform the same operations we use when dequeuing, without actually removing the element
//
//  Merge end Quick sorts are most commonly used over HeapSort
//  However, due to the small code required for its implementation, it can be used when
//  code size matters, e.g. embedded system

#include <vector>
#include <iostream>

namespace Heap{

namespace {

template <typename T>
void exch(std::vector<T> &a, int i, int j) {
    T tmp = a[i-1];
    a[i-1] = a[j-1];
    a[j-1] = tmp;
}

template <typename T>
void sink(std::vector<T> &a, int i, int N) {
    while (2*i <= N) {
        int j = 2*i;
        if (j < N && a[j-1] < a[j]) j++;
        if (a[i-1] > a[j-1]) break;
        exch(a, i, j);
        i = j;
    }
}

} // namespace

template <typename T>
void sort(std::vector<T> &a) {
    int N = a.size();
    for (int k = N/2; k >= 1; k--)
        sink(a, k, N);
    while (N > 1) {
        exch(a, 1, N--);
        sink(a, 1, N);
    }
}

} // namespace Heap


#endif // HEAPSORT_H
