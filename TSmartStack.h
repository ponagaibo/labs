#ifndef TSMARTSTACK_H_INCLUDED
#define TSMARTSTACK_H_INCLUDED

#include "TFigure.h"
#include "TSmartStackItem.h"
#include "TIterator.h"
#include <memory>
#include <future>
#include <mutex>

template <class T>
class TSmartStack {
public:
    TSmartStack();
    TSmartStack(const TSmartStack<T>& orig);

    void Push(T* figure);
    void Push(std::shared_ptr<T> figure);
    std::shared_ptr<T> Pop();
    std::shared_ptr<T> PopLast();
    std::shared_ptr<T> Top();

    bool Empty();
    size_t Size();
    void Clear();

    template <class A> friend std::ostream& operator<<(std::ostream& os,
    const TSmartStack<A>& stack);
    std::shared_ptr<T> operator[] (size_t i);

	void Sort();
	void ParallelSort();

    TIterator<TSmartStackItem<T>,T> begin();
    TIterator<TSmartStackItem<T>,T> end();

    virtual ~TSmartStack();
private:
    std::shared_ptr<TSmartStackItem<T>> head;
    std::future<void> backgroundSort();
    std::mutex sortMutex;
};

#endif // TSMARTSTACK_H_INCLUDED
