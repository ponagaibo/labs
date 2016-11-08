#ifndef TRAPEZE_H_INCLUDED
#define TRAPEZE_H_INCLUDED
#include <cstdlib>
#include <iostream>
#include "figure.h"

class FTrapeze : public Figure{
private:
    size_t side_b;
    size_t side_a;
    size_t h;
public:
    FTrapeze();
    FTrapeze(std::istream &is);
    FTrapeze(size_t side_n, size_t side_m, size_t hh);
    FTrapeze(const FTrapeze& orig);

    double Square();
    void Print();
    ~FTrapeze();
};

#endif // TRAPEZE_H_INCLUDED
