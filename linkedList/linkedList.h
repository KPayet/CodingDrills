#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class linkedList {
private:
    // helper class Node
    class Node {
    public:
        int data;
        Node *prev;
        Node *next;
        Node(int val, Node* p, Node* n):data(val), prev(p), next(n) {}
    }; // end class Node
    Node *first;
    Node *last;
public:
    linkedList() {
        first = nullptr;
        last = nullptr;
    }
};

#endif // LINKEDLIST_H
