#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED
#include <cstdlib>
#include <iostream>
#include "figure.h"

class FRectangle : public Figure{
private:
    size_t side_a;
    size_t side_b;
public:
    FRectangle();
    FRectangle(std::istream &is);
    FRectangle(size_t side_n, size_t side_m);
    FRectangle(const FRectangle& orig);

    double Square();
    void Print();
    ~FRectangle();
};

#endif // RECTANGLE_H_INCLUDED
