#include "mergesort.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <string>
#include "benchmark.h"

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
    else N = std::stoi(std::string(argv[1]));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);

    std::vector<int> v;

    for(int i=0; i<N; ++i)
        v.push_back(dis(gen));

    uint64_t startTime = GetTimeMs64();
    Merge::sort(v);
    uint64_t endTime = GetTimeMs64();

    std::cout<<(endTime - startTime)/1000<<std::endl;

    return 0;
}
