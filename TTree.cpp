#include <iostream>
#include "TTree.h"

template<class T> TTree<T>::TTree() {
    empty = true;
    children = nullptr;
    number = 0;
}

template <class T> bool TTree<T>::Empty() {
    return empty;
}

template <class T> void TTree<T>::Push(T &member) {
    if (!empty) {
        TTree<T>* newTree = new TTree;
        newTree->element = member;
        TNode* newNode = new TNode;
        newNode->treeElem = newTree;
        newNode->nextElem = children;
		children = newNode;
        number++;
    } else {
		empty = false;
        element = member;
    }
}

template <class T> T TTree<T>::Pop() {
    if (!empty) {
        T result = element;
        if (number > 0) {
            element = children->treeElem->element;
            TNode* temp = children;
            children = children->nextElem;
            number--;
            delete (temp);
        }
        else if (number == 0) {
            empty = true;
        }
        return result;
    } else {
        std::cout << "*** Tree is empty! ***" << std::endl;
        return nullptr;
    }
}

template <class T> void TTree<T>::Delete() {
    while (!Empty()) {
        Pop();
    }
}

template <class T> TTree<T>::~TTree() {}

template class TTree<void*>;
