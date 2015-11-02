#include "UF.h"

UF::UF(int N)
{
    nComponents = N;
    parent = new int[N];
    sz = new int[N];
    for(int i=0; i<N; i++) {
        parent[i] = i;  /// each site starts at the root of its own subtree
        sz[i] = 1;      /// subtree who is of size 1
    }
}

UF::~UF()
{
    delete[] parent;
    delete[] sz;
}
