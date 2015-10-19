#include "Queue.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {

    using std::cout;
    using std::endl;

    Queue q;

    for(int i=1; i<20; i++)
        q.enqueue(i);
    cout<<q.size()<<endl;
    cout<<q.peek()<<endl;

    while(!q.isEmpty())
        cout<<q.dequeue()<<endl;

    q.dequeue();

    return 0;
}
