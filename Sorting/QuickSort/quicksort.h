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
// median of 3 or Tukey's ninther for the pivot, depending on the size of the array
// and cutoff to insertion sort for arrays smaller than 7 items
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
inline void exch(std::vector<T> &a, int i, int j){
    T tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

///
/// returns the index of median of a[i], a[j]and a[k]
/// used in the computation of the pivot element for partitioning
template <typename T>
inline int medianOf3(std::vector<T> &a, int i, int j, int k) {
    return (a[i] < a[j]) ?
           ((a[j] < a[k]) ? j : ((a[i] < a[k]) ? k : i)) :
           ((a[k] < a[j]) ? j : ((a[k] < a[i]) ? k : i));
}

/// Computes the pivot element for quicksort
/// can be first element, median-of-3 approach or Tuckey's ninther
template <typename T>
T pivot(std::vector<T> &a, int lo, int hi){

    int arraySize = hi - lo + 1;

    if (arraySize <= 40) { // for small arrays, use median of 3
        int m = medianOf3(a, lo, lo + arraySize/2, hi);
        return a[m];
    }
    else  {     // use Tukey ninther
        int eps = arraySize/8;
        int mid = lo + arraySize/2;
        int median1 = medianOf3(a, lo, lo + eps, lo + eps + eps);
        int median2 = medianOf3(a, mid - eps, mid, mid + eps);
        int median3 = medianOf3(a, hi - eps - eps, hi - eps, hi);
        int ninther = medianOf3(a, median1, median2, median3);
        return a[ninther];
    }
}

/// quicksort algorithm:
/// Cutoff to insertion sort for small sub-arrays +
/// 3-way partitioning +
/// median-of-3 pivot or Tukey's ninther
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
void sort(std::vector<T> &a) {
    sort(a, 0, a.size()-1);    // does all the work, but stays in the shadows...
}

} // namespace Quick

#endif // QUICKSORT_H
