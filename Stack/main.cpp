#include "LStack.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {

    using std::cout;
    using std::endl;

    LStack<double> s;

    for(int i=1; i<10; i++)
        s.push(i+0.5);

    cout<<s.size()<<endl;

    while(!s.isEmpty())
        cout<<s.pop()<<endl;

    if(s.isEmpty())
        cout<<"Empty!!"<<endl;

    return 0;
}
