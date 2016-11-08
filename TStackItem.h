#ifndef TSTACKITEM_H_INCLUDED
#define TSTACKITEM_H_INCLUDED
#include "Square.h"

class TStackItem {
public:
    TStackItem(const TSquare& square);
    TStackItem(const TStackItem& orig);
    TStackItem* SetNext(TStackItem* next);
    TStackItem* GetNext();
    TSquare GetSquare() const;
    friend std::ostream& operator<<(std::ostream& os, const TStackItem& obj);
    virtual ~TStackItem();
private:
    TSquare square;
    TStackItem *next;
};

#endif // TSTACKITEM_H_INCLUDED
