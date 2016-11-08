#ifndef TSMARTSTACKITEM_H_INCLUDED
#define TSMARTSTACKITEM_H_INCLUDED

#include <memory>
#include "TFigure.h"

class TSmartStackItem {
public:
    TSmartStackItem(const std::shared_ptr<TFigure>& figure);
    friend std::ostream& operator<<(std::ostream& os, const TSmartStackItem& obj);
    std::shared_ptr<TSmartStackItem> SetNext(std::shared_ptr<TSmartStackItem> &next);
    std::shared_ptr<TSmartStackItem> GetNext();
    std::shared_ptr<TFigure> GetFigure() const;
    void Print();
    virtual ~TSmartStackItem();
private:
    std::shared_ptr<TFigure> figure;
    std::shared_ptr<TSmartStackItem> next;
};

#endif // TSMARTSTACKITEM_H_INCLUDED
