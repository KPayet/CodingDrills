#include "BST.h"
#include <iostream>


int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    BST<int, int> *tree = new BST<int, int>();

    tree->put(8, 18);
    tree->put(5, 15);
    tree->put(9, 19);
    tree->put(3, 13);
    tree->put(6, 16);
    tree->put(7, 17);
    tree->put(1, 11);
    tree->put(4, 14);
    tree->put(2, 12);
    tree->put(10, 110);

    auto v = *(tree->items());
    for(auto k: v)
        cout<<k<<endl;

    delete tree;

    return 0;
}
