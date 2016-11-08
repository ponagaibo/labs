#include "TStackItem.h"
#include <iostream>

TStackItem::TStackItem(const TSquare& square) {
    this->square = square;
    this->next = nullptr;
}
TStackItem::TStackItem(const TStackItem& orig) {
    this->square = orig.square;
    this->next = orig.next;
}
TStackItem* TStackItem::SetNext(TStackItem* next) {
    TStackItem* old = this->next;
    this->next = next;
    return old;
}
TStackItem* TStackItem::GetNext() {
    return this->next;
}
TSquare TStackItem::GetSquare() const {
    return this->square;
}
std::ostream& operator<<(std::ostream& os, const TStackItem& obj) {
    os << "[" << obj.square << "]" << std::endl;
    return os;
}
TStackItem::~TStackItem() {
    delete next;
}
