#include "mergesort.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <string>

int main(int argc, char *argv[])
{
//    std::vector<int> v {9,7,3,6,8,4,9,1,13,12,1,0,9,7};
//
//    Merge::sort(v);
//
//    for(auto x: v)
//        std::cout<<x<<std::endl;

    int N = 1000;
    if(argc < 2)
        std::cout<<"Usage: ./main 500 \n Defaulting to 1000"<<std::endl;
    else N = std::stoi(string(argv[1]));


    return 0;
}
