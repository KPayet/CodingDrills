#include "mergesort.h"

namespace Merge{

namespace {

void merge(std::vector<int> &a, std::vector<int> &aux, int lo, int mid, int hi){

    // We merge a[lo:mid] with a[mid+1:hi]
    int i = lo, j = mid+1;

    for (int k = lo; k <= hi; k++)
        aux[k] = a[k];

    /// now we copy-back to a, but in sorted order
    /// Merging is simply comparing each element of the two sub-arrays with indexes i and j defined above
    /// and copy the smallest on to the original array, while incrementing the corresponding index.
    /// We simply need to be careful with the sub-arrays limit, i.e. watch out for when i>mid, or j>hi
    for (int k = lo; k <= hi; k++){
        // taking care of limit cases
        // basically, if we have already reached the limit of one sub-array,
        // we simply copy the rest of the other one to a.
        if (i > mid) a[k] = aux[j++];
        else if (j > hi ) a[k] = aux[i++];
        else if (aux[j] < aux[i]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }
}

void sort(std::vector<int> &a, std::vector<int> &aux, int lo, int hi){

    if(hi <= lo) return; // an array of one element is already sorted

    /// mergesort consists in splitting the array in two
    /// and recursively sort each part
    int mid = lo + (hi - lo)/2;

    /// Recursive sorting of each part
    /// i.e. Divide...
    sort(a, aux, lo, mid);
    sort(a, aux, mid+1, hi);

    /// ...and Conquer
    /// We merge the two sorted sub-arrays back together
    merge(a, aux, lo, mid, hi);
}
}

void sort(std::vector<int> &a) {
    std::vector<int> aux(a.size(), 0);   // mergesort is not in place and requires an auxiliary array
    sort(a, aux, 0, a.size()-1);    // does all the work, but stays in the shadows...
}

}
