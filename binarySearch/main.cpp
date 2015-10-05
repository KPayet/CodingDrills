#include <iostream>
#include "binarySearch.h"
#include <vector>

int main(void) {
    
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    std::cout<<search(v, 4)<<std::endl;
    
    return 0;
}