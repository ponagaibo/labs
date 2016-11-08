#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include <cstdlib>
#include <iostream>
#include "figure.h"

class FSquare : public Figure{
private:
    size_t side;
public:
    FSquare();
    FSquare(std::istream &is);
    FSquare(size_t side_n);
    FSquare(const FSquare& orig);

    double Square();
    void Print();
    ~FSquare();
};

#endif // SQUARE_H_INCLUDED
