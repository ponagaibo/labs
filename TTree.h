#ifndef TTREE_H_INCLUDED
#define TTREE_H_INCLUDED

#include <iostream>

template<class T> class TTree {
public:
    TTree();
    T Pop();
    void Push(T& elem);
    bool Empty();
    void Delete();
    ~TTree();

    typedef struct TNode {// List
        TTree<T>* treeElem; // elem
        TNode* nextElem; // next
        TNode() {
            nextElem = nullptr;
            treeElem = nullptr;
        }
        virtual ~TNode() {
            nextElem = nullptr;
        }
    } TNode;

    T element; // node
    TNode* children;
    bool empty;
    unsigned int number; //children_size
};

#endif // TTREE_H_INCLUDED
