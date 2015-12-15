#include <iostream>
#include "HashTable.h"

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    HashTable<int, double> *t = new HashTable<int, double>();

    cout<<t->size()<<endl;

    t->put(1, 11.1);

    cout<<t->size()<<endl;

    if(t->get(1)) cout<<*(t->get(1))<<endl;

    if(t->get(2)) cout<<*(t->get(1))<<endl;

    t->remove(2);

    cout<<t->size()<<endl;

    t->remove(1);

    cout<<t->size()<<endl;

    delete t;

    return 0;
}
