#include "TSmartStack.h"
#include <iostream>

template <class T> TSmartStack<T>::TSmartStack() : head(nullptr) {}

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
        item->Print();
        item = item->GetNext();
    }
    return os;
}

template <class T> TSmartStack<T>::~TSmartStack() {
    head = nullptr;
}

#include "TFigure.h"
template class TSmartStack<TFigure>;
template std::ostream& operator<<(std::ostream& os, const TSmartStack<TFigure>& obj);
