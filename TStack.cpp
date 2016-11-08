#include "TStack.h"

TStack::TStack() : head(nullptr) {}

TStack::TStack(const TStack& orig) {
    head = orig.head;
}

void TStack::Push(TSquare square) {
    TStackItem *other = new TStackItem(square);
    other->SetNext(head);
    head = other;
}

bool TStack::Empty() {
    return head == nullptr;
}

TSquare TStack::Pop() {
    TSquare result;
    if (head != nullptr) {
        TStackItem *old_head = head;
        head = head->GetNext();
        result = old_head->GetSquare();
        old_head->SetNext(nullptr);
        delete old_head;
    }
    return result;
}
std::ostream& operator<<(std::ostream& os, const TStack& stack) {
    TStackItem* item = stack.head;
    while(item != nullptr) {
      os << *item;
      item = item->GetNext();
    }
    return os;
}

TStack::~TStack() {
    delete head;
    head = nullptr;
}
