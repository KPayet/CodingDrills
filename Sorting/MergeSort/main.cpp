#include "mergesort.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <string>
#include "benchmark.h"
#include <algorithm>

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
    std::uniform_real_distribution<> dis(0, 10000000);

    std::vector<double> v;

    for(int i=0; i<N; ++i)
        v.push_back(dis(gen));

    uint64_t startTime = GetTimeMs64();
    std::sort(v.begin(), v.end());
    uint64_t endTime = GetTimeMs64();
    std::cout<<"std::sort: "<<N<<" "<<(endTime - startTime)<<std::endl;

    if(std::is_sorted(v.begin(), v.end()))
        std::cout<<"Sorted!"<<std::endl;

    /// Now, my implementation
    std::vector<double> v2;

    for(int i=0; i<N; ++i)
        v2.push_back(dis(gen));

    uint64_t startTime = GetTimeMs64();
    Merge::sort(v2);
    uint64_t endTime = GetTimeMs64();
    std::cout<<"\nMerge::sort: "<<N<<" "<<(endTime - startTime)<<std::endl;

    if(std::is_sorted(v2.begin(), v2.end()))
        std::cout<<"Sorted!"<<std::endl;

    return 0;
}
