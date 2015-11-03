#include "UF.h"

UF::UF(int N) {
    nComponents = N;
    parent = new int[N];
    sz = new int[N];
    for(int i=0; i<N; i++) {
        parent[i] = i;  /// each site starts at the root of its own subtree
        sz[i] = 1;      /// subtree who is of size 1
    }
}

UF::~UF() {
    delete[] parent;
    delete[] sz;
}

///
/// Like explained in UF.h, union sets the root of smaller subtree to the bigger one
///
void UF::union(int p, int q) {

    int pRoot = find(p);
    int qRoot = find(q);

    /// if the sites are already connected, do nothing
    if(pRoot == qRoot) return;

    /// Again, we simply connect the root of the smaller subtree to the root of the bigger one
    if(sz[pRoot] < sz[qRoot]) { parent[pRoot] = qRoot; sz[qRoot] += sz[pRoot]; }
    else { parent[qRoot] = pRoot; sz[pRoot] += sz[qRoot]; }

    count--; /// we just connected two components, so we have one less
}

int UF::find(int p) {

    int root = p;

    while(root != parent[root]) /// this here is the find routine. A site is represented by the root of its subtree
        root = parent[root];

    /// This second part is called path compression
    /// It is meant solely as an optimization step
    /// It allows to get trees that are even shallower
    /// In terms of performance, Weighted Quick Union guarantees O(logN) time for union and find
    /// With path compression, we get ~O(1) time, i.e. nearly constant (even if not really)
    while(p != root) {
        int newp = p;
        parent[p] = root;
        p = newp;
    }

    return root;
}
