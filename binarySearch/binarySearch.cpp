#include "binarySearch.h"

int search(const std::vector<int> &a, const int &key) {
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