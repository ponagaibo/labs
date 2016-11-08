#include "TSmartStackItem.h"
#include <iostream>

template <class T> TSmartStackItem<T>::TSmartStackItem(const std::shared_ptr<T>& figure) {
    this->figure = figure;
    this->next = nullptr;
    //std::cout << "Stack item: created" << std::endl;
}

template <class T> std::shared_ptr<TSmartStackItem<T>>
TSmartStackItem<T>::SetNext(std::shared_ptr<TSmartStackItem<T>> &next) {
    std::shared_ptr<TSmartStackItem<T>> old = this->next;
    this->next = next;
    return old;
}

template <class T>std::shared_ptr<T> TSmartStackItem<T>::GetFigure() const {
    return this->figure;
}

template <class T>std::shared_ptr<TSmartStackItem<T>> TSmartStackItem<T>::GetNext() {
    return this->next;
}

template <class T>TSmartStackItem<T>::~TSmartStackItem() {
    std::cout << "Stack item: deleted" << std::endl;
}

template <class T> void TSmartStackItem<T>::Print() {
    figure->Print();
}

template <class A> std::ostream& operator<<(std::ostream& os, const TSmartStackItem<A>& obj) {
    os << "[" << obj.figure << "]" << std::endl;
    return os;
}

#include "TFigure.h"
template class TSmartStackItem<TFigure>;
template std::ostream& operator<<(std::ostream& os, const TSmartStackItem<TFigure>& obj);
