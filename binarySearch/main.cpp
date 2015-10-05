#include <iostream>
#include "binarySearch.h"
#include <vector>

int main(void) {
    
    std::vector<int> a ({1,2,3,4,5,6,7,8,9});
    std::cout<<search(a, 4)<<std::endl;
    
    return 0;
}