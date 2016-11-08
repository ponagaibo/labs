#ifndef TSTACK_H_INCLUDED
#define TSTACK_H_INCLUDED
#include "Square.h"
#include "TStackItem.h"

class TStack {
public:
    TStack();
    TStack(const TStack& orig);

    void Push(TSquare square);
    bool Empty();
    TSquare Pop();
    friend std::ostream& operator<<(std::ostream& os, const TStack& stack);
    virtual ~TStack();
private:
    TStackItem *head;
};


#endif // TSTACK_H_INCLUDED
