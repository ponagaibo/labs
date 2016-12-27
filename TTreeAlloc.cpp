#include <iostream>
#include "TTreeAlloc.h"

template<class T>
TTreeAlloc<T>::TTreeAlloc() {
    empty = true;
    children = nullptr;
    number = 0;
    treeSize = 0;
}

template <class T>
bool TTreeAlloc<T>::Empty() {
    return empty;
}

template <class T>
void TTreeAlloc<T>::Push(T &member) {
    if (!empty) {

        //treeMutex.lock();
        TTreeAlloc<T>* newTree = new TTreeAlloc;
        newTree->element = member;
        TNode* newNode = new TNode;
        newNode->treeElem = newTree;
        newNode->nextElem = children;
		children = newNode;
        number++;
        //treeMutex.unlock();
    } else {
        //treeMutex.lock();
		empty = false;
        element = member;
        //treeMutex.unlock();
    }
    treeSize++;
    //std::cout << "** NOW SIZE IS: " << treeSize << ", AND NUMBER IS: " << number << std::endl;

}

template <class T>
T TTreeAlloc<T>::Pop() {
    if (!empty) {
        T result = element;
        //treeMutex.lock();
        if (number > 0) {
            element = children->treeElem->element;
            TNode* temp = children;
            children = children->nextElem;
            number--;
            delete (temp);
        } else if (number == 0) {
            empty = true;
        }
        treeSize--;
        //treeMutex.unlock();
        return result;
    } else {
        std::cout << "*** Tree is empty! ***" << std::endl;
        return nullptr;
    }
}

template <class T>
void TTreeAlloc<T>::Delete() {
    while (!Empty()) {
        Pop();
    }
}

template <class T>
TTreeAlloc<T>::~TTreeAlloc() {}

template class TTreeAlloc<void*>;
