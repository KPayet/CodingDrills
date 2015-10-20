#include "Queue.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {

    using std::cout;
    using std::endl;

    Queue<double> q;

    for(int i=1; i<1000; i++)
        q.enqueue(i+0.5);

    cout<<q.size()<<endl;

    while(!q.isEmpty())
        cout<<q.dequeue()<<endl;

    if(q.isEmpty())
        cout<<"Empty!!"<<endl;

    return 0;
}
