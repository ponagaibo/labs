#include "TSmartStackItem.h"
#include <iostream>

template <class T> TSmartStackItem<T>::TSmartStackItem(const std::shared_ptr<T>& figure) {
    this->figure = figure;
    this->next = nullptr;
    //std::cout << "Stack item: created" << std::endl;
}

template <class T> TSmartStackItem<T>::TSmartStackItem(const std::shared_ptr<TSmartStackItem<T>>& orig) {
    this->figure = orig->figure;
    this->next = orig->next;
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
    if (this->figure) return this->next;
    else return nullptr;
}

template <class T> void TSmartStackItem<T>::Print() {
    figure->Print();
}

template <class A> std::ostream& operator<<(std::ostream& os, const TSmartStackItem<A>& obj) {
    obj.figure->Print();
    return os;
}

template <class T>TSmartStackItem<T>::~TSmartStackItem() {
    //figure = nullptr;
    //next = nullptr;
}

#include "TFigure.h"
template class TSmartStackItem<TFigure>;
template std::ostream& operator<<(std::ostream& os, const TSmartStackItem<TFigure>& obj);
