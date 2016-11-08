#ifndef TSMARTSTACK_H_INCLUDED
#define TSMARTSTACK_H_INCLUDED

#include "TFigure.h"
#include "TSmartStackItem.h"
#include <memory>

template <class T> class TSmartStack {
public:
    TSmartStack();
    void Push(std::shared_ptr<T> &&figure);
    bool Empty();
    std::shared_ptr<T> Pop();
    template <class A> friend std::ostream& operator<<(std::ostream& os, const TSmartStack<A>& stack);
    virtual ~TSmartStack();
private:
    std::shared_ptr<TSmartStackItem<T>> head;
};

#endif // TSMARTSTACK_H_INCLUDED
