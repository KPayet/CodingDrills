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
//  namely, the sink and exch functions.
//  HeapSorting is simply reordering an array so that it satisfies heap property,
//  and then perform the same operations we use when dequeuing, without actually removing the element
//
//  Merge and Quick sorts are most commonly used over HeapSort
//  However, due to the small code required for its implementation, it can be used when
//  code size matters, e.g. embedded system
//
//  Usage:
//  std::vector<int> a { ... };
//  Heap::sort(a);

#include <vector>

namespace Heap{

namespace {

template <typename T>
void exch(std::vector<T> &a, int i, int j) {
    T tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

template <typename T>
void sink(std::vector<T> &a, int i, int N) {
    ///
    /// In HeapSort, the binary heap is a Max heap, meaning that the children are smaller than their parent.
    /// To sort, we simply perform the same operations as dequeue:
    ///     i - swap first element in array a[0] (largest) with the last one a[N-1]
    ///    ii - sink the new first element
    /// This way, by iteratively putting the max element last in the array, we end up with a sorted array.
    ///
    while (2*i+1 <= N-1) {
        int j = 2*i+1;
        if (j < N-1 && a[j] < a[j+1]) j++;
        if (a[i] > a[j]) break;
        exch(a, i, j);
        i = j;
    }
}

} // namespace

template <typename T>
void sort(std::vector<T> &a) {
    
    int N = a.size();
    
    // Rearrange array so that it satisfies the heap property for a MAX heap
    for (int k = N/2; k >= 0; k--)
        sink(a, k, N);
    
    // And now, we simply swap repeatedly the first element with the last one, 
    // and restore the heap property each time
    while (N > 1) {
        exch(a, 0, --N);
        sink(a, 0, N);
    }
}

} // namespace Heap


#endif // HEAPSORT_H
