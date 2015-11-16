#include <iostream>
#include "PQ.h"
#include <vector>
#include <random>
#include "benchmark.h"
#include <algorithm>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    MinPQ<double> *pq = new MinPQ<double>();

    /// Generate random input vector
    const int N = 4000000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 100000);

    std::vector<double> v;
    for(int i=0; i<N; ++i)
        v.push_back(dis(gen));

    for(auto x: v) {
        pq->enqueue(x);
    }

    ///
    /// And here we can start the test, by enqueuing each time the same number in a queue of variable size
    ///

    const int N2 = 200000;
    std::vector<double> v2;
    for(int i=0; i<N2; ++i)
        v2.push_back(dis(gen));

    uint64_t starttime = GetTimeMs64();
    for(auto x: v2) {
        pq->enqueue(x);
    }
    uint64_t endtime = GetTimeMs64();
    cout<<"average enqueue time "<<N<<" "<<static_cast<double>(endtime-starttime)/N2<<endl;

    starttime = GetTimeMs64();
    for(int i=0; i<N2; i++) {
        pq->dequeue();
    }
    endtime = GetTimeMs64();
    cout<<"average dequeue time "<<N<<" "<<static_cast<double>(endtime-starttime)/N2<<endl;

    return 0;
}
