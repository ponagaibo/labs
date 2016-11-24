#ifndef TSMARTSTACK_H_INCLUDED
#define TSMARTSTACK_H_INCLUDED

#include "TFigure.h"
#include "TSmartStackItem.h"
#include "TIterator.h"
#include <memory>

template <class T>
class TSmartStack {
public:
    TSmartStack();
    TSmartStack(const TSmartStack<T>& orig);

    void Push(std::shared_ptr<T> &&figure);
    bool Empty();
    std::shared_ptr<T> Pop();
    template <class A> friend std::ostream& operator<<(std::ostream& os, const TSmartStack<A>& stack);

    TIterator<TSmartStackItem<T>,T> begin();
    TIterator<TSmartStackItem<T>,T> end();

    virtual ~TSmartStack();
private:
    std::shared_ptr<TSmartStackItem<T>> head;
};

#endif // TSMARTSTACK_H_INCLUDED
