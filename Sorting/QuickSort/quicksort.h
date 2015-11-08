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

namespace Quick{

namespace {

const int cutoffToInsertionSort = 7;

///
/// Insertion sort implementation used for arrays smaller than a cutoff
///
template <typename T>
void insertionSort(std::vector<T> &a, int lo, int hi){
    for (int i = lo; i <= hi; ++i)
        for (int j = i; j > lo && a[j] < a[j-1]; --j) {
            T tmp = a[j];
            a[j] = a[j-1];
            a[j-1] = tmp;
        }
}

template <typename T>
void partition(std::vector<T> &a, int lo, int hi, int p){

}

///
///
template <typename T>
void sort(std::vector<T> &a, int lo, int hi){

    if(hi <= lo + cutoffToInsertionSort){ // for small arrays, we cut to insertion sort
        insertionSort(a, lo, hi);
        return;
    }

}
} // namespace

template <typename T>
void sort(std::vector<T> &a) {
    sort(a, 0, a.size()-1);    // does all the work, but stays in the shadows...
}

} // namespace Quick

#endif // QUICKSORT_H
