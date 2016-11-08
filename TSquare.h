#ifndef TSQUARE_H_INCLUDED
#define TSQUARE_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include "TFigure.h"

class TSquare : public TFigure{
private:
    size_t side;
public:
    TSquare();
    TSquare(std::istream &is);
    TSquare(size_t side_n);
    TSquare(const TSquare& orig);

    TSquare& operator=(const TSquare& rightSq);
    friend std::ostream& operator<<(std::ostream& os, const TSquare& obj);
    void Print();
    virtual ~TSquare();
};

#endif // TSQUARE_H_INCLUDED
