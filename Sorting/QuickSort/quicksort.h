#ifndef QUICKSORT_H
#define QUICKSORT_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// quicksort.h
// This header implements a template sorting function, using quicksort algorithm
// It can be used to sort any type that implements comparison operators
// It uses 3-way partitioning, median pf 3 pivot and cutoff to insertion sort for arrays smaller than 7 items
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <vector>
#include <algorithm>    // std::random_shuffle

namespace Quick{

namespace {

const int cutoffToInsertionSort = 7;

///
/// Insertion sort implementation used for arrays smaller than a cutoff
///
template <typename T>
void insertionSort(std::vector<T> &a, int lo, int hi){

    if(hi <= lo) return;

    for (int i = lo; i <= hi; ++i)
        for (int j = i; j > lo && a[j] < a[j-1]; --j) {
            T tmp = a[j];
            a[j] = a[j-1];
            a[j-1] = tmp;
        }
}

/// swaps two values in vector a
template <typename T>
void exch(std::vector<T> &a, int i, int j){
    T tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

/// Computes the pivot element for quicksort
/// can be first element, median-of-3 approach or Tuckey's ninther
template <typename T>
T pivot(std::vector<T> &a, int lo, int hi){
    return a[lo];
}

///
/// quicksort algorithm:
/// Cutoff to insertion sort for small sub-arrays +
/// 3-way partitioning +
/// median-of-3 pivot
template <typename T>
void sort(std::vector<T> &a, int lo, int hi){

    if(hi <= lo + cutoffToInsertionSort){ // for small arrays, we cut to insertion sort
        insertionSort(a, lo, hi);
        return;
    }

    /// do 3-way partitioning

    int lt = lo, gt = hi;
    int i = lo;
    int v = pivot(a, lo, hi);

    while(i <= gt) {
        T x = a[i];

        if(x < v) exch(a, i++, lt++);
        else if(x > v) exch(a, i, gt--);
        else i++;
    }
    /// done. Now all items == v are in place,
    /// all items smaller than v are in a[lo:lt-1]
    /// and items greater than v are in a[gt+1:hi]

    /// Simply to sort recursively

    sort(a, lo, lt-1);
    sort(a, gt+1, hi);
}
} // namespace

template <typename T>
void sort(std::vector<T> &a) {
    std::random_shuffle(a.begin(), a.end());
    sort(a, 0, a.size()-1);    // does all the work, but stays in the shadows...
}

} // namespace Quick

#endif // QUICKSORT_H
