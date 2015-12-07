#ifndef LLRBT_H
#define LLRBT_H

// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// LLRBT.H
//  This file declares a template class that describes a key-value pair data structure based on LLRB-BST
//  Left-Leaning Red-Black Binary Search Tree
//  The implementation is pretty close to that of BST.h, but it also introduces the concept of color
//  that allows to balance the Binary Search Tree, i.e. keep its maximum height to a minimum value (logN).
//  Since, in a BST, complexity is dictated by the maximum depth (height of tree), such structure allows to guarantee O(logN) performance.
//  In fact, LLRB-BST data structure is a different representation of 2-3 tree (see https://en.wikipedia.org/wiki/2%E2%80%933_tree).
//  2-3 tree are self-balancing trees that are perfect to implement ordered symbol tables with high performances (low complexity).
//  But the implementation can be a little tricky.
//  LLRB-BST solves this problem by representing 3-nodes (see wikipedia description) by simple nodes connected through a RED edge.
//  BLACK edges are standard edges that connect parent Node to children Nodes.
//  The important properties of a LLRB-BST:
//
//
//  It supports basic operations: put, get, remove, contains, isEmpty
//  + ordered operations getMin and getMax (return Item data associated with min/max key)
//
// Author: Kevin Payet
// ---------------------------------------------------------------------------


#endif // LLRBT_H
