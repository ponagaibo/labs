#include "TSmartStack.h"
#include <iostream>

TSmartStack::TSmartStack() : head(nullptr) {}

void TSmartStack::Push(std::shared_ptr<TFigure> &&figure) {
    std::shared_ptr<TSmartStackItem> other(new TSmartStackItem(figure));
    other->SetNext(head);
    head = other;
}

bool TSmartStack::Empty() {
    return head == nullptr;
}

std::shared_ptr<TFigure> TSmartStack::Pop() {
    std::shared_ptr<TFigure> result;
    if (head != nullptr) {
        result = head->GetFigure();
        head = head->GetNext();
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const TSmartStack stack) {
    std::shared_ptr<TSmartStackItem> item(stack.head);
    while(item != nullptr) {
        item->Print();
        item = item->GetNext();
    }
    return os;
}

TSmartStack::~TSmartStack() {
}
