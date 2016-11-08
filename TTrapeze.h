#ifndef TTRAPEZE_H_INCLUDED
#define TTRAPEZE_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include "TFigure.h"

class TTrapeze : public TFigure{
private:
    size_t side_a;
    size_t side_b;
    size_t h;
public:
    TTrapeze();
    TTrapeze(std::istream &is);
    TTrapeze(size_t side_n, size_t side_m, size_t hh);
    TTrapeze(const TTrapeze& orig);

    TTrapeze& operator=(const TTrapeze& rightTr);
    friend std::ostream& operator<<(std::ostream& os, const TTrapeze& obj);
    double SquareOfFigure();
    void Print();
    virtual ~TTrapeze();
};

#endif // TTRAPEZE_H_INCLUDED
