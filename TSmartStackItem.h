#ifndef TSMARTSTACKITEM_H_INCLUDED
#define TSMARTSTACKITEM_H_INCLUDED

#include <memory>
#include "TFigure.h"

template<class T>
class TSmartStackItem {
public:
    TSmartStackItem(const std::shared_ptr<T>& figure);
    TSmartStackItem(const std::shared_ptr<TSmartStackItem<T>>& orig);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TSmartStackItem<A>& obj);
    std::shared_ptr<TSmartStackItem<T>> SetNext(std::shared_ptr<TSmartStackItem> &next);
    std::shared_ptr<TSmartStackItem<T>> GetNext();
    std::shared_ptr<T> GetFigure() const;
    void Print();
    virtual ~TSmartStackItem();
private:
    std::shared_ptr<T> figure;
    std::shared_ptr<TSmartStackItem<T>> next;
};

#endif // TSMARTSTACKITEM_H_INCLUDED
