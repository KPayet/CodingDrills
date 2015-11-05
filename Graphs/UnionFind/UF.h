#ifndef UF_H
#define UF_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// UF.H
// This class represents a Union-Find data structure, used to maintain dynamic information
// about the connectivity of graphs.
// It supports the union and find operations, along with a connected operation for determining whether
// two sites are in the same component and a count operation that
// returns the total number of components.
//
// The present implementation uses Weighted Quick Union, with path compression.
// Performances are:
//  O(N) for creation of a data structure with N nodes
//  O(logN) for union, find and connected operations.
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------

#include <stdint.h>

///
/// The weighted Quick Union implementation uses a tree representation for our data
/// Each site has a parent site, except for the root of a subtree which is its own parent
/// In this representation, a connected component corresponds to one subtree
/// So, sites are connected if they belong to the same subtree
/// The "trick" of UF data structure is that we only care about overall connectivity
/// not about the paths that connect two sites.
/// So, we don't need a traditional tree implementation, with Nodes etc.
/// All we require is an array (i.e. parent array below), to maintain the connectivity information
///
class UF
{
private:
        const int32_t nSites;
        int32_t nComponents;  // number of connected components
        ///
        /// The tree structure is entirely defined by the parent array
        ///
        int32_t *parent; // parent[i] gives the parent of site i
        ///
        /// The sz array is why this implementation is called Weighted
        /// In the simple Quick Union implementation, when doing union between two sites,
        /// we set the root of the subtree of one of the sites to be equal to the root of the other subtree
        /// i.e. we randomly connect one of the subtrees to the other one
        /// But, this can cause efficiency problems, because trees get tall (large depth)
        /// Weighting solves this problem by connecting the SMALLER tree to the bigger one.
        /// And the information about the sizes of subtrees is stored inside this sz array...
        ///
        int32_t *sz;    // sz[i] gives the size of the subtree with root i

public:
        ///
        /// Initializes a Union-Find data structure with N sites
        ///
        UF(int32_t N);

        ~UF();

        /// Union(p, q) connects the two subtrees that contain sites p and q
        void Union(int32_t p, int32_t q);
        /// Find(p) returns the component that contains site p
        int32_t Find(int32_t p);
        /// Are two sites connected, i.e. are they in the same component?
        bool connected(int32_t p, int32_t q);

        int32_t count() {return nComponents;}
        int32_t sites() {return nSites;}
};

#endif // UF_H
