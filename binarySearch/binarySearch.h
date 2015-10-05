#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
#include <vector>

template <typename T>
int search(const std::vector<T> &a, T key){
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