#ifndef MERGESORT_H
#define MERGESORT_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// mergesort.H
// This header simply implements a template sorting function, using mergesort algorithm
// It can be used to sort any type that implements comparison operators
// The algorithm implements a cutoff to insertion sort for arrays smaller than 7 items
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <vector>

namespace Merge{

namespace {

const int cutoffToInsertionSort = 7;

template <typename T>
void merge(std::vector<T> &aux, std::vector<T> &a, int lo, int mid, int hi){

    // We merge a[lo:mid] with a[mid+1:hi]
    int i = lo, j = mid+1;

    /// now we copy-back to a, but in sorted order
    /// Merging is simply comparing each element of the two sub-arrays with indexes i and j defined above
    /// and copy the smallest one to the original array, while incrementing the corresponding index.
    /// We simply need to be careful with the sub-arrays limit, i.e. watch out for when i>mid, or j>hi
    for (int k = lo; k <= hi; ++k){
        // taking care of limit cases
        // basically, if we have already reached the limit of one sub-array,
        // we simply copy the rest of the other one to a.
        if (i > mid) a[k] = aux[j++];
        else if (j > hi ) a[k] = aux[i++];
        else if (aux[j] < aux[i]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }
}

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

///
/// Actual implementation of recursive mergesort
/// Cuts to insertion sort for small sub-arrays
/// Merge sort uses Divide & Conquer:
/// We divide the array in two pieces, and recursively sort each piece
/// The actual sorting is done by the merge function above
///
template <typename T>
void sort(std::vector<T> &aux, std::vector<T> &a, int lo, int hi){

    if(hi <= lo + cutoffToInsertionSort){ // for small arrays, we cut to insertion sort
        insertionSort(a, lo, hi);
        return;
    }

    /// mergesort consists in splitting the array in two
    /// and recursively sort each part
    int mid = lo + (hi - lo)/2;

    /// Recursive sorting of each part
    /// i.e. Divide...
    sort(a, aux, lo, mid);
    sort(a, aux, mid+1, hi);

    /// ...and Conquer
    /// We merge the two sorted sub-arrays back together
    merge(aux, a, lo, mid, hi);
}
} // namespace

template <typename T>
void sort(std::vector<T> &a) {
    std::vector<T> aux = a;   // mergesort is not in place and requires an auxiliary array
    sort(aux, a, 0, a.size()-1);    // does all the work, but stays in the shadows...
}

} // namespace Merge


#endif // MERGESORT_H
