#ifndef TSQUARE_H_INCLUDED
#define TSQUARE_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include "TFigure.h"

class TSquare : public TFigure{
private:
    size_t side;
    static TAllocationBlock allocator;
public:
    TSquare();
    TSquare(size_t side_n);
    TSquare(const TSquare& orig);
    TSquare(std::istream &is);

    friend std::ostream& operator<<(std::ostream& os, const TSquare& obj);
    friend std::istream& operator>>(std::istream& is, TSquare& obj);
    friend TSquare operator+(const TSquare& left, const TSquare& right);
    TSquare& operator++();
    bool operator==(const TSquare& rightSq);
    TSquare& operator=(const TSquare& rightSq);
    void* operator new (size_t size);
    void operator delete(void *pointer);
    double SquareOfFigure();
    void Print();

    virtual ~TSquare();
};

#endif // TSQUARE_H_INCLUDED
