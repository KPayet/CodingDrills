#include "mergesort.h"
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    std::vector<int> v {9,7,3,6,8,4,9,1,13,12,1,0,9,7};

    Merge::sort(v);

    for(auto x: v)
        std::cout<<x<<std::endl;

    return 0;
}
