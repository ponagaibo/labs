#include "TSmartStack.h"
#include <iostream>

template <class T> TSmartStack<T>::TSmartStack() : head(nullptr) {}

template <class T> TSmartStack<T>::TSmartStack(const TSmartStack<T>& orig) {
    head = orig.head;
}

template <class T> void TSmartStack<T>::Push(std::shared_ptr<T> &&figure) {
    std::shared_ptr<TSmartStackItem<T>> other(new TSmartStackItem<T>(figure));
    other->SetNext(head);
    head = other;
}

template <class T> bool TSmartStack<T>::Empty() {
    return head == nullptr;
}

template <class T> std::shared_ptr<T> TSmartStack<T>::Pop() {
    std::shared_ptr<T> result;
    if (head != nullptr) {
        result = head->GetFigure();
        head = head->GetNext();
    }
    return result;
}

template <class T> std::ostream& operator<<(std::ostream& os, const TSmartStack<T>& stack) {
    std::shared_ptr<TSmartStackItem<T>> item(stack.head);
    while(item != nullptr) {
        os << *item;
        //item->Print();
        item = item->GetNext();
    }
    return os;
}

template <class T> TIterator<TSmartStackItem<T>, T> TSmartStack<T>::begin() {
    return TIterator<TSmartStackItem<T>, T>(head);
}

template <class T> TIterator<TSmartStackItem<T>, T> TSmartStack<T>::end() {
    return TIterator<TSmartStackItem<T>, T>(nullptr);
}

template <class T> TSmartStack<T>::~TSmartStack() {
    /*
    std::cout << "deleting stack ..." << std::endl;
    while (!(this->Empty())) {
        this->Pop();
    }
    if (this->Empty()) std::cout << "emptyyyy" << std::endl;
    head = nullptr;
    std::cout << "Stack deleted" << std::endl;
    */
    head = nullptr;
}

#include "TFigure.h"
template class TSmartStack<TFigure>;
template std::ostream& operator<<(std::ostream& os, const TSmartStack<TFigure>& obj);

