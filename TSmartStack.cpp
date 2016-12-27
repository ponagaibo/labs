#include "TSmartStack.h"
#include <iostream>


template <class T>
TSmartStack<T>::TSmartStack() : head(nullptr) {}

template <class T>
TSmartStack<T>::TSmartStack(const TSmartStack<T>& orig) {
    sortMutex.lock();
    head = orig.head;
    sortMutex.unlock();
}

template <class T>
void TSmartStack<T>::Push(std::shared_ptr<T> figure) {
    sortMutex.lock();
    std::shared_ptr<TSmartStackItem<T>> other(new TSmartStackItem<T>(figure));
    other->SetNext(head);
    head = other;
    sortMutex.unlock();
}

template <class T>
void TSmartStack<T>::Push(T* figure) {
    sortMutex.lock();
    std::shared_ptr<TSmartStackItem<T>> other(new TSmartStackItem<T>(figure));
    other->SetNext(head);
    head = other;
    sortMutex.unlock();
}

template <class T>
bool TSmartStack<T>::Empty() {
    return head == nullptr;
}

template <class T>
size_t TSmartStack<T>::Size() {
    sortMutex.lock();
    int result = 0;
    for (auto i : * this) result++;
    sortMutex.unlock();
    return result;
}

template <class T>
std::shared_ptr<T> TSmartStack<T>::Pop() {
    sortMutex.lock();
    std::shared_ptr<T> result;
    if (head != nullptr) {
        result = head->GetFigure();
        head = head->GetNext();
    }
    sortMutex.unlock();
    return result;
}

template <class T>
std::shared_ptr<T> TSmartStack<T>::PopLast() {
    sortMutex.lock();
    std::shared_ptr<T> result;
    if (head != nullptr) {
        std::shared_ptr<TSmartStackItem<T>> elem = head;
        std::shared_ptr<TSmartStackItem<T>> prev = nullptr;
        while (elem->GetNext() != nullptr) {
            prev = elem;
            elem = elem->GetNext();
        }
        if (prev != nullptr) {
            prev->SetNext(nullptr);
            result = elem->GetFigure();
        } else {
            result = elem->GetFigure();
            head = nullptr;
        }
    }
    sortMutex.unlock();
    return result;
}

template <class T>
std::shared_ptr<T> TSmartStack<T>::Top() {
    sortMutex.lock();
    if (head != nullptr) {
        return head->GetFigure();
    } else {
        return nullptr;
    }
    sortMutex.unlock();
}

template <class T>
void TSmartStack<T>::Clear() {
    while (!this->Empty()) this->Pop();
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TSmartStack<T>& stack) {
    std::shared_ptr<TSmartStackItem<T>> item(stack.head);
    os << "\tIN STACK" << std::endl;
    while(item != nullptr) {
        os << *item;
        //item->Print();
        item = item->GetNext();
    }
    return os;
}

template <class T>
std::shared_ptr<T> TSmartStack<T>::operator[](size_t i) {
    sortMutex.lock();
    if (i > Size() - 1)
        throw std::invalid_argument("** Index greater then stack size! **");
    size_t j = 0;
    for (std::shared_ptr<T> a : *this) {
        if (j == i) return a;
        j++;
    }
    sortMutex.unlock();
    return std::shared_ptr<T>(nullptr);
}

template <class T>
TIterator<TSmartStackItem<T>, T> TSmartStack<T>::begin() {
    return TIterator<TSmartStackItem<T>, T>(head);
}

template <class T>
TIterator<TSmartStackItem<T>, T> TSmartStack<T>::end() {
    return TIterator<TSmartStackItem<T>, T>(nullptr);
}

template <class T>
void TSmartStack<T>::Sort() {
    if (Size() > 1) {
        std::shared_ptr<T> middle = Pop();
        TSmartStack<T> left, right;
        while (!Empty()) {
            std::shared_ptr<T> item = Pop();
            if (*item < *middle) {
                left.Push(item);
            } else {
                right.Push(item);
            }
        }
        left.Sort();
        right.Sort();
        while (!left.Empty()) Push(left.PopLast());
        Push(middle);
        while (!right.Empty()) Push(right.PopLast());
    }
}

template<class T>
std::future<void> TSmartStack<T>::backgroundSort() {
    sortMutex.lock();
    std::packaged_task<void(void)>
    task(std::bind(std::mem_fn(&TSmartStack<T>::ParallelSort), this));
    std::future<void> res(task.get_future());
    std::thread th(std::move(task));
    th.detach();
    sortMutex.unlock();
    return res;
}

template <class T>
void TSmartStack<T>::ParallelSort() {
    if (Size() > 1) {
        std::shared_ptr<T> middle = PopLast();
        TSmartStack<T> left, right;
        while (!Empty()) {
            std::shared_ptr<T> item = PopLast();
            if (*item < *middle) {
                sortMutex.lock();
                left.Push(item);
                sortMutex.unlock();
            } else {
                sortMutex.unlock();
                right.Push(item);
                sortMutex.unlock();
            }
        }
        std::future<void> left_res = left.backgroundSort();
        std::future<void> right_res = right.backgroundSort();
        left_res.get();
        while (!left.Empty()) Push(left.PopLast());
        Push(middle);
        right_res.get();
        while (!right.Empty()) Push(right.PopLast());
    }
}

template <class T>
TSmartStack<T>::~TSmartStack() {}

#include "TFigure.h"
template class TSmartStack<TFigure>;
template std::ostream& operator<<(std::ostream& os, const TSmartStack<TFigure>& obj);
