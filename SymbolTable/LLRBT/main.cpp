#include <iostream>
#include "LLRBT.h"

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    LLRBT<int, double> *tree = new LLRBT<int, double>();

    tree->put(8, 1.8);
    tree->put(5, 1.5);
    tree->put(9, 1.9);
    tree->put(3, 1.3);
    tree->put(6, 1.6);
    tree->put(7, 1.7);
    tree->put(1, 1.1);
    tree->put(4, 1.4);
    tree->put(2, 1.2);
    tree->put(10, 11.10);

    cout<<*(tree->getMin())<<" "<<*(tree->getMax())<<endl;

    tree->remove(3);
    tree->remove(3);
    tree->remove(5);
    tree->remove(8);
    tree->remove(10);


    cout<<*(tree->getMin())<<" "<<*(tree->getMax())<<endl;


    delete tree;

    return 0;
}
