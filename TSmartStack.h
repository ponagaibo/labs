#ifndef TSMARTSTACK_H_INCLUDED
#define TSMARTSTACK_H_INCLUDED

#include "TFigure.h"
#include "TSmartStackItem.h"
#include <memory>

class TSmartStack {
public:
    TSmartStack();
    void Push(std::shared_ptr<TFigure> &&figure);
    bool Empty();
    std::shared_ptr<TFigure> Pop();
    friend std::ostream& operator<<(std::ostream& os, const TSmartStack stack);
    virtual ~TSmartStack();
private:
    std::shared_ptr<TSmartStackItem> head;
};

#endif // TSMARTSTACK_H_INCLUDED
