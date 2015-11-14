#include <iostream>
#include "PQ.h"
#include <vector>
#include <random>
//#include "benchmark.h"
#include <algorithm>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    MinPQ<double> *pq = new MinPQ<double>(10);

    //cout<<pq->size()<<endl;

    /// Generate random input vector
    const int N = 10000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1000);

    std::vector<double> v;
    for(int i=0; i<N; ++i)
        v.push_back(dis(gen));


    for(auto x: v) {
        pq->enqueue(x);
    }

    while(!pq->isEmpty()) {
        cout<<pq->dequeue()<<endl;
    }

    return 0;
}
