#include <iostream>
#include "HashTable.h"
#include <random>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    HashTable<int, double> *t = new HashTable<int, double>();

    cout<<t->size()<<endl;
    t->put(1, 11.1);
    if(t->get(1)) cout<<*(t->get(1))<<endl;
    if(t->get(2)) cout<<*(t->get(1))<<endl;
    t->remove(2);
    t->remove(1);
    if(t->get(1)) cout<<*(t->get(1))<<endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> doubleDis(0, 10000);
    std::uniform_int_distribution<> intDis(1, 1000);

    for(int i=0; i < 10000; ++i) {
        t->put(intDis(gen), doubleDis(gen));
    }

    cout<<t->size()<<endl;

    for(int i=0; i<20; ++i) {
        int k = intDis(gen);
        if(t->get(k)) cout<<*(t->get(k))<<endl;
    }

    for(int i=0; i<300; ++i) {
        int k = intDis(gen);
        t->remove(k);
    }

    cout<<t->size()<<endl;

    delete t;

    return 0;
}
