#include <iostream>
#include "PQ.h"
#include <vector>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    PQ *pq = new PQ(10);

    //cout<<pq->size()<<endl;

    std::vector<int> v{1,2,3,4,5,6,12,54,21,1,1,56,8,10,10,8,100,6};

    for(auto x: v) {
        pq->enqueue(x);
    }

    while(!pq->isEmpty()) {
        cout<<pq->dequeue()<<endl;
    }

    return 0;
}
