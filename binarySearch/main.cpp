#include <iostream>
#include "binarySearch.h"
#include <vector>

int main(void) {
    
    vector<int> a = {1,2,3,4,5,6,7,8,9};
    std::cout<<search(a, 4)<<endl;
    
    return 0;
}