#include "TSmartStackItem.h"
#include <iostream>

TSmartStackItem::TSmartStackItem(const std::shared_ptr<TFigure>& figure) {
    this->figure = figure;
    this->next = nullptr;
    //std::cout << "Stack item: created" << std::endl;
}

std::shared_ptr<TSmartStackItem> TSmartStackItem::SetNext(std::shared_ptr<TSmartStackItem> &next) {
    std::shared_ptr<TSmartStackItem> old = this->next;
    this->next = next;
    return old;
}

std::shared_ptr<TFigure> TSmartStackItem::GetFigure() const {
    return this->figure;
}

std::shared_ptr<TSmartStackItem> TSmartStackItem::GetNext() {
    return this->next;
}

TSmartStackItem::~TSmartStackItem() {
    std::cout << "Stack item: deleted" << std::endl;
}

void TSmartStackItem::Print() {
    figure->Print();
}

std::ostream& operator<<(std::ostream& os, const TSmartStackItem& obj) {
    os << "[" << obj.figure << "]" << std::endl;
    return os;
}
