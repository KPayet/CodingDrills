#include <iostream>
#include "heapsort.h"
#include <random>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
    const int N = 1000;

    ///
    /// Generate random input vector
    ///
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 10000000);

    std::vector<double> v;
    for(int i=0; i<N; ++i)
        v.push_back(dis(gen));


    /// Sort with std::sort

    std::vector<double> v1 = v; // so that I use the exact same inputs
    std::sort(v1.begin(), v1.end());

    /// Now, with Heap::sort

    std::vector<double> v2 = v; // so that I use the exact same inputs

    Heap::sort(v2);
    /// check that both outputs are equal
    if( v1 == v2 )
	std::cout<<"\n\nSame result!"<<std::endl;

    return 0;
}
