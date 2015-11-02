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

class UF
{
public:
        UF();

private:
        unsigned int m_Counter;
};

#endif // UF_H
