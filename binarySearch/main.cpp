#include <iostream>
#include "binarySearch.h"
#include <vector>

int main(void) {
    
    std::vector<double> v{1.1,2.2,3.5,4.5,5.6,6.7,7.8,8.4,9.4};
    std::cout<<search(v, 4.5)<<std::endl;
    
    return 0;
}
