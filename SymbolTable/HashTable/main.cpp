#include <iostream>
#include "HashTable.h"

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    HashTable<int, double> *t = new HashTable<int, double>();

    cout<<t->size()<<endl;

    t->put(1, 11.1);

    delete t;

    return 0;
}
