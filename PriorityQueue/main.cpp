#include <iostream>
#include "PQ.h"
#include <vector>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    PQ *pq = new PQ(10);

    cout<<pq->size()<<endl;

    std::vector<int> v{1,2,3,4,5,6,7,8,9};

    pq->enqueue(2);
    cout<<pq->size()<<endl;
    cout<<pq->dequeue()<<endl;
    cout<<pq->size()<<endl;

    return 0;
}
