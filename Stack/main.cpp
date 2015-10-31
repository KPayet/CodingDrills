#include "LStack.h"
#include "Stack.h"


#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {

    using std::cout;
    using std::endl;

    LStack<double> s;

    for(int i=1; i<10; i++)
        s.push(i+0.5);

    while(!s.isEmpty())
        cout<<s.pop()<<endl;

    Stack<double> s2;

    for(int i=1; i<10; i++){
        s2.push(i+0.5);
    }

    cout<<s2.size()<<endl;

    while(!s2.isEmpty())
        cout<<s2.pop()<<endl;

    return 0;
}
