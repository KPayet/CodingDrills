#ifndef MERGESORT_H
#define MERGESORT_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// UF.H
// This header simply implements a template sorting function, using mergesort algorithm
// It can be used to sort any type that implements comparison operators
// The algorithm implements a cutoff to insertion sort for arrays smaller than 10 items
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <vector>

namespace Merge{

namespace {

const int cutoffToInsertionSort = 20;

template <typename T>
void merge(std::vector<T> &a, std::vector<T> &aux, int lo, int mid, int hi){

    // We merge a[lo:mid] with a[mid+1:hi]
    int i = lo, j = mid+1;

//    for (int k = lo; k <= hi; k++)
//        aux[k] = a[k];

    /// now we copy-back to a, but in sorted order
    /// Merging is simply comparing each element of the two sub-arrays with indexes i and j defined above
    /// and copy the smallest one to the original array, while incrementing the corresponding index.
    /// We simply need to be careful with the sub-arrays limit, i.e. watch out for when i>mid, or j>hi
    for (int k = lo; k <= hi; ++k){
        // taking care of limit cases
        // basically, if we have already reached the limit of one sub-array,
        // we simply copy the rest of the other one to a.
        if (i > mid) aux[k] = a[j++];
        else if (j > hi ) aux[k] = a[i++];
        else if (a[j] < a[i]) aux[k] = a[j++];
        else aux[k] = a[i++];
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

template <typename T>
void sort(std::vector<T> &a, std::vector<T> &aux, int lo, int hi){

    if(hi <= lo + cutoffToInsertionSort){ // for small arrays, we cut to insertion sort
        insertionSort(aux, lo, hi);
        return;
    }

    /// mergesort consists in splitting the array in two
    /// and recursively sort each part
    int mid = lo + (hi - lo)/2;

    /// Recursive sorting of each part
    /// i.e. Divide...
    sort(aux, a, lo, mid);
    sort(aux, a, mid+1, hi);

    /// ...and Conquer
    /// We merge the two sorted sub-arrays back together
    merge(a, aux, lo, mid, hi);
}
} // namespace

template <typename T>
void sort(std::vector<T> &a) {
    std::vector<T> aux(a.size(), 0);   // mergesort is not in place and requires an auxiliary array
    sort(aux, a, 0, a.size()-1);    // does all the work, but stays in the shadows...
}

} // namespace Merge


#endif // MERGESORT_H
