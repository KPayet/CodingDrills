#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
#include <vector>

// Use of a template function so that it can be used with any type of data
// PROVIDED it implements/overloads the comparison operators
// Important note: Binary search is only meant for sorted arrays !!!
template <typename T>
int search(const std::vector<T> &a, const T &key){
    int lo = 0;
    int hi = a.size()-1;
    
    while(lo<=hi) {
        int mid = lo + (hi -lo)/2;
        if(key<a[mid]) hi = mid - 1;
        else if(key>a[mid]) lo = mid+1;
        else return mid;
    }
    return -1;
}

#endif