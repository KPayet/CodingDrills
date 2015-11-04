#include "UF.h"
#include <cassert>

UF::UF(int N): nSites(N) {
    assert(N>0 && "Trying to instantiate UF data structure with negative number of sites!");

    nComponents = N;
    parent = new int[N];
    sz = new int[N];
    for(int i=0; i<N; i++) {
        parent[i] = i;  /// each site starts as the root of its own subtree
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
void UF::Union(int p, int q) {

    assert( ((p > 0 && p < nSites) && (q > 0 && q < nSites)) &&
           "Index site out-of-bounds. Make sure index is positive, and smaller than number of sites" );

    int pRoot = Find(p);
    int qRoot = Find(q);

    /// if the sites are already connected, do nothing
    if(pRoot == qRoot) return;

    /// Again, we simply connect the root of the smaller subtree to the root of the bigger one
    if(sz[pRoot] < sz[qRoot]) { parent[pRoot] = qRoot; sz[qRoot] += sz[pRoot]; }
    else { parent[qRoot] = pRoot; sz[pRoot] += sz[qRoot]; }

    --nComponents; /// we just connected two components, so we have one less

    return;
}

int UF::Find(int p) {

    assert( (p > 0 && p < nSites) && "Index site out-of-bounds. Make sure index is positive, and smaller than number of sites" );

    while(p != parent[p]) { /// this here is the Find routine. A site is represented by the root of its subtree
        ///
        /// When we say that we implement path compression, it only means adding the following line
        /// Path compression modifies the subtrees in a way that the maximum depth tends to 1
        /// i.e. after many find, the sites end up being connected directly to the root
        /// i.e. for a subtree of size N, the root will have N-1 children sites, and in turn these sites shouldn't have children
        /// Note that the text above describes an ideal case. We might never reach such perfect configuration,
        /// but simply trying to achieve it still improves performance.
        ///
        parent[p] = parent[parent[p]];
        p = parent[p];
    }

    return p;
}

/// trivial
bool UF::connected(int p, int q) {

    assert( ((p > 0 && p < nSites) && (q > 0 && q < nSites)) &&
           "Index site out-of-bounds. Make sure index is positive, and smaller than number of sites" );

    return Find(p) == Find(q);
}
