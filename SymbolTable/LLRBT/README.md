#Left-Leaning Red-Black Binary Search Tree

LLRB-BST emulates 2-3 tree (in this implementation), which are BST that are self-balanced. This allows to correct the problem introduced by the traditional Hibbert deletion scheme, that unbalances the height of Binary Search Trees. 

Since performance in such data structure is dictated mainly by the depth of the tree, this allows to implement symbol table data structures (here, associative array) while guarantying logN performance for all basic operations, i.e. insertion, search and deletion.

The implementation here should work fine, is free of memory leaks (tested with valgrind). However, I haven't tested performances yet, even though I don't think there should be any problem there...
