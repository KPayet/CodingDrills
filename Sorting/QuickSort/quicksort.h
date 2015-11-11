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
// It uses 3-way partitioning, precisely the Bentley-McIlroy 3-way partitioning
// and cutoff to insertion sort for arrays smaller than 7 items
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <vector>
#include <algorithm>
#include <random>

namespace Quick{

namespace {

const int cutoffToInsertionSort = 7;

/// swaps two values in vector a
template <typename T>
inline void exch(std::vector<T> &a, int i, int j){
    T tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

///
/// Insertion sort implementation used for arrays smaller than a cutoff
///
template <typename T>
void insertionSort(std::vector<T> &a, int lo, int hi){

    if(hi <= lo) return;

    for (int i = lo; i <= hi; ++i)
        for (int j = i; j > lo && a[j] < a[j-1]; --j) {
            exch(a, j, j-1);
        }
}

/// quicksort algorithm:
/// Cutoff to insertion sort for small sub-arrays +
/// 3-way partitioning
template <typename T>
void sort(std::vector<T> &a, int lo, int hi){

    if(hi <= lo + cutoffToInsertionSort){ // for small arrays, we cut to insertion sort
        insertionSort(a, lo, hi);
        return;
    }

    // Bentley-McIlroy 3-way partitioning
    // It gives a whole ~40% improvement in time performance !!!
    // See http://www.sorting-algorithms.com/static/QuicksortIsOptimal.pdf, page 9
        int i = lo, j = hi+1;
        int p = lo, q = hi+1;
        T v = a[lo];
        while (true) {
            while (a[++i] < v)
                if (i == hi) break;
            while (v < a[--j])
                if (j == lo) break;

            if (i == j && a[i] == v)
                exch(a, ++p, i);
            if (i >= j) break;

            exch(a, i, j);
            if (a[i] == v) exch(a, ++p, i);
            if (a[j] == v) exch(a, --q, j);
        }


        i = j + 1;
        for (int k = lo; k <= p; k++)
            exch(a, k, j--);
        for (int k = hi; k >= q; k--)
            exch(a, k, i++);

        sort(a, lo, j);
        sort(a, i, hi);
}
} // namespace

template <typename T>
void sort(std::vector<T> &a, bool shuffle = false) {
    if(shuffle) {
        auto engine = std::default_random_engine{};
        std::shuffle(a.begin(), a.end(), engine);
    }
    sort(a, 0, a.size()-1);    // does all the work, but stays in the shadows...
}

} // namespace Quick

#endif // QUICKSORT_H
