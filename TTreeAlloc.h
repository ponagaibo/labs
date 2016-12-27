#ifndef TTREE_H_INCLUDED
#define TTREE_H_INCLUDED

#include <iostream>
#include <mutex>

template<class T> class TTreeAlloc {
public:
    TTreeAlloc();
    T Pop();
    void Push(T& elem);
    bool Empty();
    void Delete();
    ~TTreeAlloc();
private:
    typedef struct TNode {// List
        TTreeAlloc<T>* treeElem; // elem
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
    unsigned int number;
    size_t treeSize;
    //std::mutex treeMutex;
};

#endif // TTREE_H_INCLUDED
