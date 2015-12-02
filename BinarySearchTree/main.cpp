#include "BST.h"
#include <iostream>


int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    BST<int, int> *tree = new BST<int, int>();

    tree->put(8, 8);
    tree->put(5, 5);
    tree->put(9, 9);
    tree->put(3, 3);
    tree->put(6, 6);
    tree->put(7, 7);
    tree->put(1, 1);
    tree->put(4, 4);
    tree->put(2, 2);
    tree->put(10, 10);

    auto v = *(tree->keys());
    for(auto k: v)
        cout<<k<<endl;

    delete tree;

    return 0;
}
